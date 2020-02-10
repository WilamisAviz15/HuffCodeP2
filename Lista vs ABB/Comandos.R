par(mfrow=c(1,2))

list_c <- read.csv(file.choose(), header=TRUE, sep=",")
plot(list_c$list, ylab="Comparações", xlab="Valores", main="LISTA",bty="l", tcl=0.3, col = "red")

size_abb <- read.csv(file.choose() , header=TRUE, sep=",")
plot(size_abb$abb, ylab="Comparações", xlab="Valores", main="ABB",bty="l",xlim =c(0,2000), ylim=c(0,2000),tcl=0.3, col = "blue")
