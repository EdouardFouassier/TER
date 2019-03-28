#Pour compiler : R CMD BATCH "draw.R"

fileStat = "stat.data"
data = read.table(fileStat)
attach(data);

nbTask = V1
TauxFF = V2
TauxAL = V3


plot(nbTask, TauxFF, type = "n", ylim = range(c(TauxFF, TauxAL)), xlab = "Nombre de taches", ylab = "Taux de complétion")
lines(nbTask, TauxFF, col = "blue")
lines(nbTask, TauxAL, col = "red")
legend("topright", col=c("blue", "red"), legend=c("TauxFF", "TauxAL"), lty=1:1, box.lty=0)

