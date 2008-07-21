# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/AcdDigi/SConscript,v 1.1 2008/07/09 21:13:39 glastrm Exp $
# Authors: Heather Kelly <heather@milkyway.gsfc.nasa.gov>
# Version: AcdDigi-03-03-01

Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('AcdDigiLib', depsOnly = 1)
AcdDigiLib = libEnv.SharedLibrary('AcdDigi', listFiles(['src/*.cxx', 'src/Dll/*.cxx']))

progEnv.Tool('AcdDigiLib')
progEnv.Tool('identsLib')
progEnv.Tool('EventLib')
progEnv.Tool('xmlBaseLib')
test_AcdDigiUtil = progEnv.GaudiProgram('test_AcdDigiUtil', listFiles(['src/test/util/*.cxx']), test = 1)
test_AcdDigi = progEnv.GaudiProgram('test_AcdDigi', listFiles(['src/test/*.cxx']), test = 1)

progEnv.Tool('registerObjects', package = 'AcdDigi', libraries = [AcdDigiLib],
             testApps = [test_AcdDigiUtil, test_AcdDigi], includes = listFiles(['AcdDigi/*.h']))