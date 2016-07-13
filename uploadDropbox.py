# parameter 1 = file to upload
# enviroment variable DROPBOX_SECRET = app authorization key

import dropbox
import os
import sys
import subprocess

# Get the version
#----------------
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

file_name = "imebra_" + release.replace('.', '_') + '.zip'

# Upload to dropbox
#------------------
client = dropbox.client.DropboxClient(os.environ['DROPBOX_SECRET'])

f = open(sys.argv[1], 'rb')
response = client.put_file(file_name, f)
f.close()
