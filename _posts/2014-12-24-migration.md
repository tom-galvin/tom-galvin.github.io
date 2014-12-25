---
layout: post
title: "The Migration: moving to GitHub Pages"
date: 2014-12-24 13:31:52
summary: Describing the movement of username.password to the GitHub Pages service.
categories: blog gen
---
Prior to this point, the entirety of username.password has been written in PHP, and hosted with [x10hosting](http://x10hosting.com)'s free service. While this does the job temporarily, I don't like using PHP for any longer than is absolutely necessary, as PHP seems to have been designed with the express purpose of producing unmaintainable, ugly code - something that I don't want to be dealing with several years down the line. I was also having some issues with the email service as x10hosting has blacklisted the *.pw* ccTLD (due to the relatively high volume of spam originating from such sites), meaning I couldn't send any email from my site. x10hosting is good, but not ideal.

Today I've finally made the move to something more permanent. All of the articles (not that there were many anyway) were already written in Markdown on the old site, meaning the move to Jekyll and GitHub pages only made sense. I'm using the Pixyll theme for this site, which matches the simplicity of the old site and also has the added bonus of being better on mobile readers.

My domain registrar, Namecheap, has a fairly good DNS service, meaning I can point the website traffic to GitHub and the email to another service I use. Slightly confusingly, the Namecheap control panel presents two different options for DNS settings; one being far more limited than the other. To use MX, A or CNAME records, you must choose the more obscure option. A found this after a bit of head-scratching, and got my records pointing to their respective places.

Setting up GitHub Pages was the pleasant bit. I've already used GitHub extensively to manage personal projects and A-level Computing coursework, meaning there were few hitches getting the backbone of the site sitting up straight. Jekyll seems nice enough to work with - it has essentially the same workflow as what I was using before, except with HTML generated beforehand using Ruby rather than HTML generated on the fly using PHP. I like Ruby and have used it before, meaning getting Jekyll configured on my end for testing was also painless.

After that procedure, the site is now up and running! Writing the content is the next item on the agenda - that's part of the New Year resolution for 2015. In the unlikely event that you had actually seen the old site and still want to view it, you can access it at [usnpw.x10host.com](http://usnpw.x10host.com/), where you can use the SQLite sandbox *sqool* that is set up there.
