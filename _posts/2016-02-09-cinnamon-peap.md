---
layout: post
title: Using PEAP-secured WLAN with Cinnamon and Arch
date: 2016-02-09 00:29:17
summary: After hours of wrestling with Eduroam, I've finally nailed the solution.
categories: blog tech
---
Some wireless networks such as Eduroam make use of a family of authentication protocols known as EAP, which replaces the standard passphrase-based WPA security (or worse, open networks with MAC address authentication) with a username and password based system. Some networks refer to this security as *802.1x*. The one I encounter the most is the wireless network *eduroam*, which permeates through most universities and higher education sites in the UK. However, the default Cinnamon setup with *NetworkManager* refused to work well with such networks at all, and just refused to connect. Here is how I solved this issue.

*If you're trying to connect to Eduroam, read this paragraph, otherwise, skip this step.* The first thing to do is to navigate to [Eduroam's CAT service](https://cat.eduroam.org/), which provides assistance to connecting to eduroam. Click on the blue button labelled **"eduroam user: download your eduroam installer"**, select your institution, download the relevant script and save it to your home directory (or wherever). You'll then want to run the script (whether it fails or not doesn't seem to matter) and then check in your `~/.cat_installer` directory to see if a file exists named `ca.pem`. This is the certificate I seemed to need in order to be able to connect to Eduroam.

The next step is to run `nm-connection-editor` (it might be in a separate package - it's in a package called `nm-connection-editor` if you're on Arch using pacman). Click **Add**, choose **Wi-Fi** and fill in the following details in the tabs in the following window (you might also want to give your network a unique name at the top of this window, this dpesn't need to be the same as the network's SSID).

### Wi-Fi

**SSID**: The SSID of the network, exactly as it's spelled.  
**Mode**: Client

### Wi-Fi Security

**Security**: WPA & WPA2 Enterprise  
**Authentication**: Protected EAP (PEAP)  
**Identity**: *Your login username, eg. your email address (*abc123@uni.ac.uk*)*  
**CA certificate**: If Eduroam, the `ca.pem` file obtained earlier. Otherwise, tick "*No CA certificate is required*".  
**PEAP version**: Automatic  
**Inner Authentication**: MSCHAPv2 (for Eduroam, at least)  
**Username**: Same as **Identity**  
**Password**: Your login password  

Save these details now, and you should automatically connect.
