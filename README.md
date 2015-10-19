#Serial Code for atmega644
I've included a makefile, just change  
`programmer = usbtiny`  
to  
`programmer = dragon_isp`  
and run make install and it should work out

scanf and printf are working properly.  
I also created a shortcut function for printf called print which just automatically addes a \n to the 
end of the printf function so  
`print("hello world");`  
is equivalent to  
`printf("hello world\n");`  
It also still works with variables so  
`print("%s %c %i", string1, char1, number1);`  
is the same as  
`printf("%s %c %i\n", string1, char1, number1);`  
