#!/usr/bin/env python
import praw,os
from pprint import pprint
import ConfigParser as configparser
from urlgrabber import urlgrab
# Load config
config = configparser.RawConfigParser()
config.read('background.cfg')

link = config.get('Reddit','link')
directory = config.get('Wallpaper','directory')

print("Getting images from " + link)
print("Writing images to " + directory)

# Connecting reddit
r = praw.Reddit(user_agent='backgroundChanger v 0.1 by sQu4rks')
subreddit = r.get_subreddit(link)
links = []
for submission in subreddit.get_hot(limit=50):
	if str(submission.url).endswith(".jpg"):
		links.append(str(submission.url))


# Download 9 images
for i in range(1,len(links)):
	filename = urlgrab(links[i])
	newFilename = directory + str(i) + ".jpg"
	print(newFilename)
	os.rename(filename,newFilename)
