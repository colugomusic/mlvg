#!/usr/bin/env python3

import shutil
import sys
import os
import ntpath

# TODD collect all *.cpp *.h files in dirs so we don't have to be adding
# new files all the time

targetFiles = ["source/au/audiounitconfig.h", "source/au/Info.plist", 
	"resource/plugin.rc", "source/version.h",
	"source/parameters.h",
	"source/vg/MLVGPrefixHeader.h",
	"source/pluginProcessor.cpp", "source/pluginProcessor.h", 
	"source/pluginController.cpp", "source/pluginController.h",
	"source/pluginEditorView.cpp", "source/pluginEditorView.h", 
	"source/factoryDefinition.cpp", "CMakeLists.txt",
	"source/mac/objCPrefix.h"]

def path_leaf(path):
    head, tail = ntpath.split(path)
    return tail or ntpath.basename(head)

def replaceInFile(searchText, replaceText, filePath):
	if os.path.exists(filePath):
		# search and replace, creating temp file
		input = open(filePath)
		inputStr = input.read()
		input.close()
		if inputStr.count(searchText) > 0:
			output = open(filePath, 'w')
			output.write(inputStr.replace(searchText, replaceText))
			output.close()
			print ("    replaced", searchText, "with", replaceText, "in", path_leaf(filePath))
	else:
		print(filePath, " not found.")
		return

def replaceAttrInFiles(attr, value):
	cwd = os.getcwd()

	validAttr = True
	searchText = ''
	searchTextLowercase = ''

	if(attr == 'name'):
		searchText = 'llllPluginNamellll'
		searchTextLowercase = 'llllpluginnamellll'
	elif(attr == 'company'):
		searchText = 'llllCompanyllll'
		searchTextLowercase = 'llllcompanyllll'
	elif(attr == 'subtype'):
		searchText = 'lxxl'
	elif(attr == 'mfgr'):
		searchText = 'LXXL'
	elif(attr == 'url'):
		searchText = 'llllCompanyURLllll'
	elif(attr == 'email'):
		searchText = 'lllllCompanyEmailllll'
	elif(attr == 'uida'):
		searchText = '0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA'
	elif(attr == 'uidb'):
		searchText = '0xBBBBBBBB, 0xBBBBBBBB, 0xBBBBBBBB, 0xBBBBBBBB'
	else:
		validAttr = False

	replaceText = value
	replaceTextLowercase = str.lower(replaceText)
	
	# search and replace the template attribute in all the target files.
	# not all strings we want to replace will be in all the files,
	# but for simplicity we just grind through all the files for each search anyway.
	if(validAttr):
		for file in targetFiles:
			fullName = cwd + "/" + file
			replaceInFile(searchText, replaceText, fullName)
			if searchTextLowercase != '':
				replaceInFile(searchTextLowercase, replaceTextLowercase, fullName)

	return

# allow running from cmd line
if __name__ == "__main__":
    
	# count the arguments
	arguments = len(sys.argv) - 1
	if arguments != 2:
		print("usage: setPluginInfo <attribute> <stringValue>")
		quit()
	replaceAttrInFiles(sys.argv[1], sys.argv[2])
