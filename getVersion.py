import subprocess

f = open('version.property', 'w')

hgbranch = 'hg branch'
hgprocess = subprocess.Popen(hgbranch.split(), stdout=subprocess.PIPE)
branch = hgprocess.stdout.readlines()[0].rstrip()
if branch == "default":
  branch = "4"

version = branch
if version.count('.') == 0:
  version += ".999"  
if version.count('.') == 1:
  version += ".999"

hgrelease = 'hg log -b default --template . --rev ancestors(.)'
hgprocess = subprocess.Popen(hgrelease.split(), stdout=subprocess.PIPE)
release = version + '.' + str(hgprocess.stdout.readlines()[0].count('.'))

f.write("short_version = " + version + "\n")
f.write("version = " + release + "\n")

f.close()