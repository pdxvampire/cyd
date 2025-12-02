# cyd08 - SD card - read the contents and display in Serial Monitor

## Setup
In Arduino IDE turn on Serial Monitor via Tools -> Serial Monitor.

## Expected Behavior
When you upload the sketch you should see the contents of the top level of the SD card logged in the Serial Monitor.

## Sample Output From Serial Monitor
````
15:49:45.626 ->     Entering InitializeOnboardLEDs
15:49:45.626 ->     Exiting InitializeOnboardLEDs
15:49:45.626 ->     Entering InitializeSDCard
15:49:45.626 ->         SD card initialisation done.
15:49:45.626 ->         SD Card Type: SDHC
15:49:45.626 ->         SD Card Size: 7MB
15:49:45.659 ->     Exiting InitializeSDCard
15:49:45.659 ->     ####### CALL LISTDIR (1 level deep) ########
15:49:45.659 ->     Listing directory: /
15:49:45.659 ->         DIR: System Volume Information
15:49:45.659 ->         DIR: LOST.DIR
15:49:45.659 ->         DIR: Music
15:49:45.659 ->         DIR: Movies
15:49:45.659 ->         DIR: Podcasts
15:49:45.659 ->         DIR: Ringtones
15:49:45.690 ->         DIR: Pictures
15:49:45.690 ->         DIR: Alarms
15:49:45.690 ->         DIR: Download
15:49:45.690 ->         DIR: Notifications
15:49:45.690 ->         DIR: DCIM
15:49:45.690 ->         DIR: Documents
15:49:45.722 ->         DIR: Audiobooks
15:49:45.722 ->         DIR: Android
15:49:45.722 ->         DIR: .android_secure
15:49:45.722 ->         DIR: Recordings
15:49:45.755 ->         FILE: btn1.jpg
15:49:45.755 ->             SIZE: 16kb
15:49:45.755 ->         FILE: 01.png
15:49:45.755 ->             SIZE: 3kb
15:49:46.414 ->         DIR: .$recycle_bin$
15:49:46.414 ->     ####### BACK FROM CALL LISTDIR ########
15:49:46.414 -> Exiting setup
````