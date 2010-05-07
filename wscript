#!/usr/bin/python

def set_options(opt):
	print '\nSetting build options & flags...'
	# We tell Waf we need a C++ compiler
	opt.tool_options('compiler_cxx')

def init():
	print 'Initializing WAF build system...'
	

def configure(conf):
	print 'Configuring the build enviroment...'
	
	conf.check_tool('compiler_cxx')
	conf.check_cfg	(package='gtkmm-2.4',at_least_version='2.0.0',args='--cflags --libs',uselib_store='GTKMM')

def build(bld):
	print 'Building the sources to objects...'
	
	bld.new_task_gen(
		features	= 'cxx cstaticlib',
		source		= 'automationwidget.cpp',
		includes	= '/usr/include',
		uselib		= 'GTKMM',
		target		= 'automationwidget',
		export_dirs	= '.'	)
	
	bld.new_task_gen(
		features	= 'cxx cprogram',
		source		= 'main.cpp',
		includes	= '/usr/include',
		uselib		= 'GTKMM',
		uselib_local= 'automationwidget',
		target		= 'test.out'	)

def shutdown():
	# this function can be used to copy files to the build directory.
	# its a little advanced, but if your using Images or other files
	# in your program, its worth knowing.
	
	import os
	import shutil
	
	if os.path.isdir(os.path.join(os.getcwd(),'build/default')):
		try:
			shutil.copy2('automate.glade','./build/default/automate.glade')
			print 'Copying new resouces...'
		except:
			print 'Copying failed. Acces denied?'
	
	print('shutting down')

