# alias
alias syu="sudo pacman -Syu"
alias re="base64 -d <<<"
alias b64="base64 <<<"
alias in="sudo pacman -Sy"
alias rzsh="source ~/.zshrc"
alias mwin="sudo mount /dev/sda2 /win"
alias mwind="sudo mount /dev/sda4 /winD"
alias musb="sudo mount /dev/sdb1 ~/pen"
alias umusb="sudo umount /dev/sdb1"
alias indwm="cd ~/.config/dwm-6.2/ && sudo make clean install && cd -"
alias lxrdb="xrdb -load .Xresources"
alias cls="clear"
alias v="nvim"
alias rmonitor="xrandr --output VGA-1 --auto --right-of eDP-1"
alias lmonitor="xrandr --output VGA-1 --auto --left-of eDP-1"
alias config='/usr/bin/git --git-dir=/home/xytor/.dotfiles/ --work-tree=/home/xytor'
# style
PROMPT='%F{#33f}%m%f%F{#ddf}@%f%F{#39f}%n%f %F{blue}%B%~%b%f > '
RPROMPT='[%F{#FFFF00}%?%f]'
# autocompletion
autoload -Uz compinit
compinit
zstyle ':completion:*' menu select
setopt COMPLETE_ALIASES

autoload -Uz add-zsh-hook

function xterm_title_precmd () {
	print -Pn -- '\e]2;%n@%m %~\a'
	[[ "$TERM" == 'screen'* ]] && print -Pn -- '\e_\005{g}%n\005{-}@\005{m}%m\005{-} \005{B}%~\005{-}\e\\'
}

function xterm_title_preexec () {
	print -Pn -- '\e]2;%n@%m %~ %# ' && print -n -- "${(q)1}\a"
	[[ "$TERM" == 'screen'* ]] && { print -Pn -- '\e_\005{g}%n\005{-}@\005{m}%m\005{-} \005{B}%~\005{-} %# ' && print -n -- "${(q)1}\e\\"; }
}

if [[ "$TERM" == (alacritty*|gnome*|konsole*|putty*|rxvt*|screen*|tmux*|xterm*|st*) ]]; then
	add-zsh-hook -Uz precmd xterm_title_precmd
	add-zsh-hook -Uz preexec xterm_title_preexec
fi
