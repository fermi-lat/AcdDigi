# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/AcdDigi/SConscript,v 1.6 2008/11/12 20:30:41 glastrm Exp $
# Authors: Heather Kelly <heather@milkyway.gsfc.nasa.gov>
# Version: AcdDigi-03-05-00

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
