@ECHO off

::-------------------------------------------------------------------
:: Environment variables needed
::-------------------------------------------------------------------
SET QTDIR=C:\Qt\5.3\msvc2013_64

::------------------------------------------------------------------
:: Create solution
::------------------------------------------------------------------
CD Premake
premake5.exe vs2013
cd ..

::------------------------------------------------------------------
:: Done
::------------------------------------------------------------------
:AllDone
pause