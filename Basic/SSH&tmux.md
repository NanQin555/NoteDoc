# SSH

## Generate ssh key
`ssh-keygen -t rsa -C "xxx@xxx.com"`

replace "xxx@xxx.com" with your e-mail

if Github ssh connect use Github e-mail

## Get public key

`cd ~/.ssh`

There will be id_rsa.pub

You can copy the public key to Github 

## Test connect

Github: `ssh -T git@github.com`

# tmux

## Easy Test

use `tmux`

or `tmux new -s name_you_like`

## SSH connect tmux

`ssh yourusername@remote_public_ip`

`tmux attach -t [ID|Name]` 

## tmux operation

`tmux ls`

creat new pane: Ctrl+b c

spilt window: Ctrl+b % or Ctrl+b "

change window: Ctrl+b p or Ctrl+b n

delete pane: Ctrl+b x

leave tmux: Ctrl+b d

`tmux kill-session -t [ID|Name]`
