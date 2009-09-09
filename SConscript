# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/AcdDigi/SConscript,v 1.13 2009/08/08 01:27:48 jrb Exp $
# Authors: Heather Kelly <heather@milkyway.gsfc.nasa.gov>
# Version: AcdDigi-03-08-01
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('AcdDigiLib', depsOnly = 1)
AcdDigi = libEnv.SharedLibrary('AcdDigi',
                               listFiles(['src/*.cxx', 'src/Dll/*.cxx']))

progEnv.Tool('AcdDigiLib')
test_AcdDigiUtil = progEnv.GaudiProgram('test_AcdDigiUtil', 
	listFiles(['src/test/util/*.cxx']), test = 1)
test_AcdDigi = progEnv.GaudiProgram('test_AcdDigi',
                                    listFiles(['src/test/*.cxx']), test = 1)

progEnv.Tool('registerTargets', package = 'AcdDigi',
             libraryCxts = [[AcdDigi, libEnv]],
             testAppCxts = [[test_AcdDigiUtil, progEnv], [test_AcdDigi,progEnv]],
             includes = listFiles(['AcdDigi/*.h']))




