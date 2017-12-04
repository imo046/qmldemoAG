/**********************************************************************************
**
** Copyright (C) 1994 Narvik University College
** Contact: GMlib Online Portal at http://episteme.hin.no
**
** This file is part of the Geometric Modeling Library, GMlib.
**
** GMlib is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** GMlib is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
**
**********************************************************************************/
#include "C:/STE6245/gmlib-50e676222977fbf777a43302e74828ed87558300/gmlib.git/modules/scene/src/visualizers/gmselectorgridvisualizer.h"
#include "C:/STE6245/gmlib-50e676222977fbf777a43302e74828ed87558300/gmlib.git/modules/parametrics/src/curves/gmpsubcurve.h"


namespace GMlib {


//*****************************************
// Constructors and destructor           **
//*****************************************
template<typename T>
GMlib::MyBCurve<T>::MyBCurve(PCurve<T,3> *c, int n)
{
    _d = 1;
//    _s  = c->getStartP();
//    _e = c->getEndP();

    _makeKnotVector(n);

    for(int i=0;i<n;i++){
        auto cu = new PSubCurve<T>(c,_t[i],_t[i+2],_t[i+1]);
        _C[i] = cu;
        this->insert(cu);
    }
}
//  template <typename T>
//  inline
//  MyBCurve<T>::MyBCurve(const DVector<Vector<T,3>> &c, int d) {
//    _d = d;
//    _makeKnotVector(c.getDim());
//    _C = c;
//    for (int i=0;i<_C.getDim();i++){
//        Selector<T,3>* s = new Selector<T,3>(_C[i],i,this);
//        this->insert(s);

//    }
//    auto sk = new SelectorGridVisualizer<T>;
//    sk->setSelectors(_C,0,isClosed());
//    this->insertVisualizer(sk);

//  }

//  template <typename T>
//  inline
//  MyBCurve<T>::MyBCurve(const DVector<Vector<T,3>> &c, int d, int n) {
//  }

  template <typename T>
  inline
  MyBCurve<T>::MyBCurve( const MyBCurve<T>& copy ) : PCurve<T,3>(copy) {}


  template <typename T>
  MyBCurve<T>::~MyBCurve() {}


  //**************************************
  //        Public local functons       **
  //**************************************


  //***************************************************
  // Overrided (public) virtual functons from PCurve **
  //***************************************************

  template <typename T>
  bool MyBCurve<T>::isClosed() const {
    return false;
  }


  //******************************************************
  // Overrided (protected) virtual functons from PCurve **
  //******************************************************

  template <typename T>
  void MyBCurve<T>::eval( T t, int d, bool /*l*/ ) const {

    this->_p.setDim( d + 1 );
    int i = _findIndex(t);

    const T b1 = 1-_B(_W(i,1,t));
    const T b2 = _B(_W(i,1,t));


//    const T b1 = (1-_W(i,1,t))*(1-_W(i-1,2,t));

//    const T b2 = ((1-_W(i,1,t))*_W(i-1,2,t))+(_W(i,1,t)*(1-_W(i,2,t)));

//    const T b3 = (_W(i,1,t)*_W(i,2,t));

//                 local curves
    this->_p = b1*_C[i-1]->evaluateParent(t,0) + b2*_C[i]->evaluateParent(t,0);//_C[i-2]*b1 + _C[i-1]*b2 + _C[i]*b3;



  }


  template <typename T>
  T MyBCurve<T>::getStartP() const {
    return _t(_d);
  }


  template <typename T>
  T MyBCurve<T>::getEndP()const {
      return _t(_C.getDim());
  }

  template<typename T>
  T MyBCurve<T>::_W(int i, int d, T t) const
  {
      return ((t - _t(i))/(_t(i+d)-_t(i)));

  }

  template<typename T>
  int MyBCurve<T>::_findIndex(T t) const
  {
    int i=_d;
    int n = _C.getDim();
    for(;i<=n;i++){
        if(t>=_t(i) && t<_t(i+1))
            break;
    }
    if (i >= n){
        i=n-1;
    }
    return i;
  }

  template<typename T>
  void MyBCurve<T>::_makeKnotVector(int n)
  {

      //n = _C.getDim();
      auto local_d = (_e-_s)/(n-1);

      _t.setDim(n+_d+1);
      _t[0] = _t[1] = _s;

      for(int i = 0;i<n;i++){
          _t[i+2] = _s+i*local_d;
      }

      _t[n] = _t[n+1] = _e;

      //        for(int i = 0;i<=_d;i++){
      //            _t[i] = 0;
      //        }
      //        for(int i=_d+1;i<= n;i++){
      //            _t[i] = i-_d;
      //        }
      //        for(int i=n+1;i<=n+_d;i++){
      //            _t[i] = _t[i-1];
      //        }
  }

  template<typename T>
  void MyBCurve<T>::_createControlPoints(const DVector<Vector<T, 3> > &p, int n)
  {
      int m = p.getDim();
      DMatrix<Vector<T,3>> A(m,n);
      for (int i = 0; i<m; i++){
          for (int j = 0; j<n;j++){
              A[i][j] = T(0);
          }
      }
//      for (int j = 0;j<m;j++){
//          A[j][findIndex(_p[0])]

//      }



  }

  template<typename T>
  T MyBCurve<T>::_B(T t) const
  {
    return 3*(t*t) - 2*(t*t*t);
  }




} // END namespace GMlib
