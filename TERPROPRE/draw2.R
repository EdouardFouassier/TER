#Pour compiler : R CMD BATCH "draw.R"

fileStat = "stat2.data"
data = read.table(fileStat)
attach(data);

nbTask = V1
TauxFF = V2
TauxAL = V3
TauxASL = V4
TauxAY = V5
minFF = V6
minAL = V7
minASL = V8
minAY = V9
maxFF = V10
maxAL = V11
maxASL = V12
maxAY = V13

plot(nbTask, TauxFF, type = "n", ylim = range(c(maxFF, maxAL, maxASL,maxAY)), xlab = "Nombre de taches", ylab = "Taux de complétion")
lines(nbTask, TauxFF, col = "blue")
lines(nbTask, TauxAL, col = "red")
lines(nbTask, TauxASL, col = "green")
lines(nbTask, TauxAY, col = "purple")

points(nbTask, minFF,col='blue',pch=19)
points(nbTask, minAL,col='red',pch=19)
points(nbTask, minASL,col='green',pch=19)
points(nbTask, minAY,col='purple',pch=19)

points(nbTask, maxFF,col='blue',pch=18)
points(nbTask, maxAL,col='red',pch=18)
points(nbTask, maxASL,col='green',pch=18)
points(nbTask, maxAY,col='purple',pch=18)

legend("topright", col=c("blue", "red", "green","purple"), legend=c("TauxFF", "TauxAL", "TauxASL","tauxAY"), lty=1:1, box.lty=0)


