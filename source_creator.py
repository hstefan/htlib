class Config:
	def __init__(self, license, namespace, template_style, block):
			self.license_filename = license
			self.namespace = namespace
			self.template_style = template_style
			self.block_prefix = block

class ConfigException(Exception):
	pass

class LockedFileException(Exception):
	pass

class TemplateArg:
	def __init__(self, name, default_value = None):
		self.name = name
		self.default_value = default_value
	def has_default_argument(self):
		return self.default_value != None

class Class:
	def __init__(self, name, template_args = None):
		self.name = name
		self.template_args = template_args
	def is_template(self):
		return self.template_args != None

def read_config(conf_file):
	try:
		with open(conf_file, "r") as config:
			line = config.readline()
			config_list = line.split(",")
			if len(config_list) > 4 or len(config_list) == 0:
				raise ConfigException
			else:
				return Config(config_list[0], config_list[1], config_list[2], config_list[3].strip('\n'))
	except IOError:
		with open(conf_file, "w") as config:
			license = raw_input("License file: ")
			namespace = raw_input("Namespace: ")
			template_style = raw_input("Template style (0 - class, 1 - typename): ")
			block_prefix = raw_input("Head Block prefix: ")
			config.write(license + "," + namespace + "," + template_style + "," +  block_prefix)
			return Config(license, namespace, template_style, block_prefix)

def request_file():
	filename = raw_input("Filename: ")
	try:
		with open(filename, 'r'):
			raise LockedFileException
	except IOError:
		return open(filename, 'w')	

def write_license(conf, ofile):
	with open(conf.license_filename, "r") as license_file:
		ofile.write("\n/*\n")
		for line in license_file:
			ofile.write(" * " + line)
		ofile.write("*/\n\n")

def create_classlist():
	op = raw_input("Create any class? (y/n) ")
	if op.lower() == "y":
		class_input = raw_input("Type the class names, separed by comma: ")
		class_names = class_input.split(',')
		class_list = []
		for name in class_names:
			name = name.replace(' ', "")
			op = raw_input("Is \"" + name + "\" a template? (y/n) ")
			
			if op.lower() == "y":
				arg_names = raw_input("Template arguments (comma separated): ")
				argnames_list = arg_names.split(',')
				print "Default arguments for \"" + name + "\""
				class_item = Class(name, [])
				
				for arg_name in argnames_list:
					arg_name = arg_name.replace(' ', '')
					arg_val = raw_input(arg_name + ": ")
					if arg_val == "":
						class_item.template_args.append(TemplateArg(arg_name))
					else:
						class_item.template_args.append(TemplateArg(arg_name, arg_val))
				
				class_list.append(class_item)
			
			elif op.lower() == "n":
				class_list.append(Class(name))
		
		return class_list
	
	elif op.lower() == "n":
		return class_list
	
	else:
		print "Invalid option."
		return create_classlist()

def write_file(ofile, config, class_list):
	write_license(config, ofile)
	ofile.write("#ifndef " + config.block_prefix + "_" + ofile.name.replace('.', '_').replace(' ', '_').upper() + "\n")
	ofile.write("#define " + config.block_prefix + "_" + ofile.name.replace('.', '_').replace(' ', '_').upper() + "\n\n")
	ofile.write("namespace " + config.namespace + "\n{\n")
	template_word = ""

	if config.template_style == "0":
		template_word = "class"
	elif config.template_style == "1":
		template_word = "typename"
	
	for class_item in class_list:
		ofile.write("\ttemplate <")
		if class_item.is_template():
			for arg in class_item.template_args:			
				ofile.write(template_word + " " + arg.name)
				if arg.has_default_argument():
					ofile.write(" = " + arg.default_value)
				if class_item.template_args[-1] != arg:
					ofile.write(", ")
				
			ofile.write(">\n")
		
		ofile.write("\tclass " + class_item.name + "\n\t{ /* your code goes here */ }\n\n")
		
	ofile.write("}\n")
	ofile.write("\n#endif")	

def check_configuration(config):
	print "Checking configuration"
	try:
		with open(config.license_filename, 'r') as license_file:
			print "License: OK"
	except IOError:			
		print "License: ERROR"
		raise ConfigException
	
	if config.template_style == "0" or config.template_style == "1":
		print "Template style: OK"
	else:
		print "Template style: ERROR"
	   	raise ConfigException	
	
	if config.namespace != "":
		print "Namespace: OK"
	else:
		print "Namespace: ERROR"
		raise ConfigException
	print ""
	

def main():
	conf_file = ".scrc"

	config = o_file = None
	try:
		config = read_config(conf_file)
		check_configuration(config)
	except ConfigException:
		print "Bad configuration, aborting."
		return

	try:		
		o_file = request_file()
	except LockedFileException:
		print "Can't modify this file. Please choose another."
		return

	class_list = create_classlist()
	write_file(o_file, config, class_list)
	o_file.close()
main()
	
