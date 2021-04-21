# nscan
It is a simple bash based program that acts like nmap for non rooted android mobiles.

## Instructions
To run the porgram you'll need the TERMUX app which can be found in the play store.  
On downloading...  
1- Run "termux-setup-storage" and allow permissions  
2- Use commands like (same as bash) to find the nscan file downloaded  
          -> "ls" to list files in current directory  
          -> "cd" to change directory  
          -> "cp" or "mv" to copy or move files across directories  
3- Being in the same directory as the 'nscan' program. Run  
`bash nscan <ip/gateway address> <lower limit> <upper limit>`  
Note: I would recomment using  
`chmod +x nscan`  
so you can run the program using  
`./nscan <ip/gateway address> <lower limit> <upper limit>`  
Example:  
  `./nscan 192.168.1.0 100 255`  
Here we are telling the program to scan all the ip addresses from 192.168.1.100 to 192.168.1.255.  

## Extra notes
 <ip/gateway address> : refers to your ip-address or router (you can find this by using the `ifconfig` in TERMUX and observing the inet value for wlan0 adapter)  
 <lower limit>        : this takes an integer value that tells the program the lowest address to start from. (includes this number)  
 <upper limit>        : this takes an integer calue that tells the porgram the highest adress to end at. (includes this number)  
  
### Thank you
Cipherkill out! *peace emoji*
