@ECHO OFF

SET BIN=arduino_debug
SET ACTION=--%1
SET BOARD=--board arduino:samd:mkrfox1200
SET PORT=--port %2
SET MAIN_INO=..\..\MKRFOX1200_Firmware.ino

%BIN% %ACTION% %BOARD% %PORT% %MAIN_INO%