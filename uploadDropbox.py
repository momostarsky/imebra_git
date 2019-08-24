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

file_name = "/imebra_" + release.replace('.', '_') + '.zip'

# Upload to dropbox
#------------------
client = dropbox.Dropbox(os.environ['DROPBOX_SECRET'])

with open(sys.argv[1], "rb") as f:
    client.files_upload(f.read(), file_name, mute = True)

