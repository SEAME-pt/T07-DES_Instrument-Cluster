# How to...

In order for an application to run everytime the linux computer based is restart, a service must me setted for taht purpose.

## Setup a service to start at boot

1. Create a file "my_executable.service":

'''
bash
sudo vim /etc/systemd/system/my_executable.service
'''

2. Fill it with the requested info:

'''bask
[unit]
Description=whatever_you_want_to_tell_about_your_service
After=network.target

[Service]
ExecStart=/home/your_login/your_service_foilder/your_service_executable_file
Restart=always
User=your_login
WorkingDirectory=/home/your_login/your_service_folder

[Install]
WantedBy=multi-user.target
''''

This the '''bash my_executable.service ''' file

3. Setup service

Now that the service file e ready, a service must be setup

  1. enale & disable service

'''bash
sudo systemctl enable my_executable.service
'''

'''bash
sudo systemctl disable my_executable.service
'''

This won't start or stop the service. It will just allow the service to start or not at boot.



  2. start & stop service

'''bash
sudo systemctl start my_executable.service
'''

'''bash
sudo systemctl stop my_executable.service
'''

This a run time action. It will launch or stop de service during the current run time.

  3. check status

'''bash
sudo systemctl status my_executable.service
'''

If the service is started the status would look like this:

'''bash
● my_executable.service - OLED223
     Loaded: loaded (/etc/systemd/system/my_executable.service; enabled; preset: enabled)
     Active: active (running) since Sat 2024-11-23 18:01:30 WET; 1h 37min ago
   Main PID: 507 (oled)
      Tasks: 5 (limit: 9289)
        CPU: 1min 53.436s
     CGroup: /system.slice/my_executable.service
             └─507 /home/team07/oled/oled
'''





