buttonPin is reversed, it's INPUT_PULLUP.
this one is a bit harder, when we push the button and hold it, it turns on a pattern, when we release it, it turns off. push it again, different pattern, release, off. it's 135, 24, 12345.
i use the mode++. what I didn't expect here: the if has to be the lastButtonState and currentButtonState to make it run only once when we push it. then back off.
and also the active puzzer which play when I push the button.
