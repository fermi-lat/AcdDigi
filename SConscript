# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/AcdDigi/SConscript,v 1.21 2010/06/15 02:46:00 jrb Exp $
# Authors: Heather Kelly <heather@milkyway.gsfc.nasa.gov>
# Version: AcdDigi-03-10-03-gr01

Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='AcdDigi', toBuild='component')
AcdDigi = libEnv.SharedLibrary('AcdDigi',
                               listFiles(['src/*.cxx', 'src/Dll/*.cxx']))

progEnv.Tool('AcdDigiLib')

test_AcdDigiUtil = progEnv.GaudiProgram('test_AcdDigiUtil', 
                                        listFiles(['src/test/util/*.cxx']),
                                        test = 1, package='AcdDigi')
test_AcdDigi = progEnv.GaudiProgram('test_AcdDigi',
                                    listFiles(['src/test/*.cxx']), test = 1)

progEnv.Tool('registerTargets', package = 'AcdDigi',
             libraryCxts = [[AcdDigi, libEnv]],
             testAppCxts = [[test_AcdDigiUtil, progEnv], [test_AcdDigi,progEnv]],
             includes = listFiles(['AcdDigi/*.h']),
             xml = ['xml/acdDigi.xml'],
             jo = ['src/test/jobOptions.txt', 'src/test/util/jobOptions.txt'])




