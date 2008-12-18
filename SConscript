# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/AcdDigi/SConscript,v 1.9 2008/12/05 17:35:45 ecephas Exp $
# Authors: Heather Kelly <heather@milkyway.gsfc.nasa.gov>
# Version: AcdDigi-03-07-00
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('AcdDigiLib', depsOnly = 1)
AcdDigi = libEnv.SharedLibrary('AcdDigi', listFiles(['src/*.cxx', 'src/Dll/*.cxx']))

progEnv.Tool('AcdDigiLib')
test_AcdDigiUtil = progEnv.GaudiProgram('test_AcdDigiUtil', 
	listFiles(['src/test/util/*.cxx']), test = 1)
test_AcdDigi = progEnv.GaudiProgram('test_AcdDigi', listFiles(['src/test/*.cxx']), test = 1)

progEnv.Tool('registerObjects', package = 'AcdDigi', libraries = [AcdDigi], testApps = [test_AcdDigiUtil, 
test_AcdDigi], includes = listFiles(['AcdDigi/*.h']))



