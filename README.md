## Compile Sync:
 - sudo -s
 - cd user_program
 - ./restart.sh
## Compile Async:
 - sudo -s
 - cd user_program
 - ./restart_bonus.sh
 ## Test:
  - ./master [file_num] [file1] [file2] ... [fileN] [mmap / fcntl]
  - ./slave [file_num] [file1] [file2] ... [fileN] [mmap / fcntl] [ip]
  ## == IMPORTANT ==
  if you want to compile from Sync to Async or from Async to Sync, you need to reboot the machine due to module problems.
