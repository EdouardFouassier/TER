#Pour compiler : R CMD BATCH "draw.R"

fileStat = "stat.data"
data = read.table(fileStat)
attach(data);

nbTask = V1
TauxFF = V2
TauxAL = V3
TauxASL = V4
TauxAY = V5


plot(nbTask, TauxFF, type = "n", ylim = range(c(TauxFF, TauxAL, TauxASL,TauxAY)), xlab = "Nombre de taches", ylab = "Taux de Réussite")
lines(nbTask, TauxFF, col = "blue")
lines(nbTask, TauxAL, col = "red")
lines(nbTask, TauxASL, col = "green")
lines(nbTask, TauxAY, col = "purple")
legend("topright", col=c("blue", "red", "green","purple"), legend=c("FirstFit", "AlgoLourd", "AlgoSuperLourd","algoPasilourd"), lty=1:1, box.lty=0)

