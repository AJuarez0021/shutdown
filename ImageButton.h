//******************************************
// Author:     Massimo Galbusera	kkez@winapizone.net
//									http://www.winapizone.net
//
// Program:    ImageButton.lib
// File:       ImageButton.h
// Created:    November 2004
// Updated:    November 2006
// Compiler:   Visual C++ 6.0
//
// NOTES:
// CreateGrayscaleIcon and CreateGrayscaleBitmap (aka
// ModifyIcon and ModifyBitmap) functions are from 
// the CButtonST class by Davide Calabro
//
// You are free to use/modify this code but leave this header intact.
// This file is public domain so you are free to use it any of
// your applications (Freeware, Shareware, Commercial). All I ask is
// that you let me know you're using this extension, so i can
// add a link to your program to my website.
//******************************************

enum ibOptions { 
    IBO_MAINTAIN = -1, 
    IBO_GRAY = -2, 
    IBO_LIGHTEN = -3
};

void ImageButton_EnableXPThemes();

BOOL ImageButton_Create(HWND button);
BOOL ImageButton_Create(HWND hwndParent, UINT ctrlID);
void ImageButton_Create(int buttonCount, ...);

BOOL ImageButton_SetBitmap(HWND button, HBITMAP normalBitmap, HBITMAP disabledBitmap=NULL, HBITMAP hoverBitmap=NULL);
BOOL ImageButton_SetBitmap(HWND button, HINSTANCE instance, UINT normalBitmap, UINT disabledBitmapId, UINT hoverBitmap);
BOOL ImageButton_SetBitmap(HWND button, UINT normalBitmapID, UINT disabledBitmapId, UINT hoverBitmapID);

BOOL ImageButton_SetIcon(HWND button, HICON normalIcon, HICON disabledIcon, HICON hoverIcon);
BOOL ImageButton_SetIcon(HWND button, HINSTANCE instance, UINT normalIconID, UINT disabledIconId, UINT hoverIconID, int iconWidth, int iconHeight);
BOOL ImageButton_SetIcon(HWND button, UINT normalIconID, UINT disabledIconId, UINT hoverIconID, int iconWidth=16, int iconHeight=16);

BOOL ImageButton_SetCursor(HWND button, HCURSOR hCursor);
BOOL ImageButton_SetCursor(HWND button, HINSTANCE instance, UINT cursorID);

BOOL ImageButtons_SetCursor(HCURSOR cursor);
BOOL ImageButtons_SetCursor(HINSTANCE instance, UINT cursorID);
