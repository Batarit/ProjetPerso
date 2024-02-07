
@echo off
title Check
:debut
if %errorlevel%== 1 (
	echo Programme1 est actif
	goto debut)

:lancez
echo Vérifier si Programme1 est actif...
TaskList | findstr /c:serveur.exe > nul
if %errorlevel%== 0(
	echo Programme1 est actif
	timeout 2
	goto lancez)
