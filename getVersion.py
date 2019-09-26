import subprocess

f = open('version.property', 'w')

hgbranch = 'hg branch'
hgprocess = subprocess.Popen(hgbranch.split(), stdout=subprocess.PIPE)
branch = hgprocess.stdout.readlines()[0].decode("utf-8").rstrip()

version = branch
if version == "default":
  version = "4"

if version.count('.') == 0:
  version += ".999"  
if version.count('.') == 1:
  version += ".999"

hgrelease = 'hg log -b ' + branch + ' --template . --rev ancestors(.)'
hgprocess = subprocess.Popen(hgrelease.split(), stdout=subprocess.PIPE)
release = version + '.' + str(hgprocess.stdout.readlines()[0].decode("utf-8").count('.'))

hgid = 'hg id -i'
hgprocess = subprocess.Popen(hgid.split(), stdout=subprocess.PIPE)
release += ' changeset ' + hgprocess.stdout.readlines()[0].decode("utf-8").rstrip()



# split the version
version_components = version.split('.')
f.write("short_version = " + version + "\n")
f.write("version = " + release + "\n")
f.write("version_major = " + version_components[0] + "\n")
f.write("version_minor = " + version_components[1] + "\n")
f.write("version_patch = " + version_components[2] + "\n")

f.close()

