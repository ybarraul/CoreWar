.name "Trampoline"
.comment "Fork to live, and live to fork"

start:
sti		r1, %:live, %1			#write id for live line
st		r16, :start				#erase number writing
ld      %0, r16					#carry at 1

premain:
sti     r1, %:front, %1			#write id for front line
st		r16, :premain			#erase number writing

main:
fork	%:front

live:
live	%1
zjmp	%:live

front:
live    %1
fork	%400
ld		%1, r2
st		r2, 500
st		r1, 499
zjmp	%:main
