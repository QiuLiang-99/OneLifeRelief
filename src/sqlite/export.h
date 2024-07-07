#ifndef _QX_EXPORT_H_
#define _QX_EXPORT_H_

#ifdef _BUILDING_QX
#define QX_DLL_EXPORT QX_DLL_EXPORT_HELPER
#else  // _BUILDING_QX
#define QX_DLL_EXPORT QX_DLL_IMPORT_HELPER
#endif // _BUILDING_QX

#ifdef _BUILDING_QX
#define QX_REGISTER_HPP_QX QX_REGISTER_HPP_EXPORT_DLL
#define QX_REGISTER_CPP_QX QX_REGISTER_CPP_EXPORT_DLL
#else // _BUILDING_QX
#define QX_REGISTER_HPP_QX QX_REGISTER_HPP_IMPORT_DLL
#define QX_REGISTER_CPP_QX QX_REGISTER_CPP_IMPORT_DLL
#endif // _BUILDING_QX

#endif // _QX_EXPORT_H_