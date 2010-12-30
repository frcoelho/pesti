# This program is under GPL Licence
# Author: David Cohen <dacohen@gmail.com>
# Version: 0.1
#
# History:
# 2007-16-04: version 0.1 implemented

r"""This module gives support to deal with assembly files that have debug informations.
@def get_c_file: this function returns the C file related to an assembly file.
@def get_afc_dict: this function returns a dictionary relating the lines of code from a C file and its assembly instructions."""

import re 

# Internal functions

def _read_file_lines(file):
	fasm = open(file, "ra")
	lines = fasm.readlines()
	fasm.close()

	return lines

def _find_asm_from_c(clines, slines):
	pattern_loc = r'^\s*\.loc\b\s+\d+\s+(\d+)\s+'
	pattern_inst = r'^\s*\b(\w+)\b\s+'
	STAT_INIT = 0
	STAT_NEW_LOC = 1
	STAT_ADD_INST_LOC = 2
	afc_dict = {}
	loc = -1
	for line in slines:
		res = re.search(pattern_inst, line)
		if res:
			# New assembly instruction to C LOC
			data = res.group(1)
			state = STAT_ADD_INST_LOC
		else:
			res = re.search(pattern_loc, line)
			if res:
				# New LOC
				data = res.group(1)
				state = STAT_NEW_LOC
			else:
				continue
		if state == STAT_INIT:
			continue
		if state == STAT_NEW_LOC:
			loc = int(data)
			if afc_dict.has_key(loc) == False:
				afc_dict[loc] = [clines[loc-1].strip()]
			continue
		if state == STAT_ADD_INST_LOC:
			if loc > 0:				
				afc_dict[loc].append(data)
			continue
	return afc_dict

# Public interfaces

def get_c_file(sfile = None, slines = None):
	"""This function returns the C file related to an assembly file with debug informations.
	@sfile: an assembly file with debug informations.
	@slines: a list of lines from an assembly file.
	You should inform at least one argument. If both are given, the sfile will be used."""

	if (sfile == None) and (slines == None):
		print "Error: you must inform at least one arg! (sfile or slines)"
		return None

	if sfile != None:
		slines = _read_file_lines(sfile)
	
	pattern = r'^\s*\.file\b\s+["]\b([a-zA-Z0-9._]+)\b'
	for line in slines:
		res = re.search(pattern, line)
		if res:
			return res.group(1)
	return None

def get_afc_dict(sfile):
	"""This function returns a dictionary relating the lines of code from a C file and its assembly instructions.
	@sfile: an assembly file with debug informations."""

	sl = _read_file_lines(sfile)
	cfile = get_c_file(slines = sl)

	if cfile == None:
		print "\nCould not find c_file from the entered asm_file."
		print "Please, check if you type the right filename."
		return None
	
	cl = _read_file_lines(cfile)
	afc_dict = _find_asm_from_c(cl, sl)

	return afc_dict

