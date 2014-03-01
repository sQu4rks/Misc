Misc
====

All kinds of patches und extensions, not big enough for there own repository

email
=====

E-Mail is a little python script that forwards a mail sent to a single e-mailadress to all adresses specified in a list file. 
In addition we have a sneaky little GUI for use in Mediawiki, so you should be ready to go with this for a small mailinglist

backgroundChanger
=================

backgroundChanger is a python script that automatically pulls the hottest pictures from a given subreddit(e.g. EarthPorn). One 
can then have his windowmanager change the pictures automatically.
For awesome this is the lua code needed
```lua
-- {{{ Function definitions

-- scan directory, and optionally filter outputs
function scandir(directory, filter)
    local i, t, popen = 0, {}, io.popen
    if not filter then
        filter = function(s) return true end
    end
    print(filter)
    for filename in popen('ls -a "'..directory..'"'):lines() do
        if filter(filename) then
            i = i + 1
            t[i] = filename
        end
    end
    return t
end

-- }}}

-- configuration - edit to your liking
wp_index = 1
wp_timeout  = 10
wp_path = "/path/to/wallpapers/"
wp_filter = function(s) return string.match(s,"%.jpg$") or string.match(s,"%.jpg$") end
wp_files = scandir(wp_path, wp_filter)
 
-- setup the timer
wp_timer = timer { timeout = wp_timeout }
wp_timer:connect_signal("timeout", function()
 
  -- set wallpaper to current index for all screens
  for s = 1, screen.count() do
    gears.wallpaper.maximized(wp_path .. wp_files[wp_index], s, true)
  end
 
  -- stop the timer (we don't need multiple instances running at the same time)
  wp_timer:stop()
 
  -- get next random index
  wp_index = math.random( 1, #wp_files)
 
  --restart the timer
  wp_timer.timeout = wp_timeout
  wp_timer:start()
end)
 
-- initial start when rc.lua is first run
wp_timer:start()
```
(Taken from https://wiki.archlinux.org/index.php/Awesome)
This script is tested with python2.7 and requires urlgrabber,configparser and praw to be installed

sentSerial
==========

Sentserial is an easy to use serial interface for python applications. 
Usage: 
	python2.7 sentSerial.py SERIALCOMMAND

replaceIt
=======
Replace is a little c++ tool to replace strings in a textfile. It's designed for auto-generated letters and similar things

Installation:
	
	```
	make
	sudo make install
	```

Usage:
	
	> replaceIt --help 
	Will print all necessery information
