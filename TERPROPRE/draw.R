#Pour compiler : R CMD BATCH "draw.R"

fileStat = "stat.data"
data = read.table(fileStat)
attach(data);

nbTask = V1
TauxFF = V2
TauxAL = V3
TauxASL = V4


plot(nbTask, TauxFF, type = "n", ylim = range(c(TauxFF, TauxAL, TauxASL)), xlab = "Nombre de taches", ylab = "Taux de complétion")
lines(nbTask, TauxFF, col = "blue")
lines(nbTask, TauxAL, col = "red")
lines(nbTask, TauxASL, col = "green")
legend("topright", col=c("blue", "red", "green"), legend=c("TauxFF", "TauxAL", "TauxASL"), lty=1:1, box.lty=0)

