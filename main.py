from Targets.TargetList import TargetList
from Targets.TargetGoogle import TargetGoogle
from Targets.TargetMasscan import TargetMasscan
from Targets.TargetShodan import TargetShodan
from Exploits.osComerceExploit import osComerceExploit
from Exploits.sshBrute import SshBrute
from frameworkCLI.Fcli import Fcli

api = Fcli()

target = TargetList("/home/juan/hacking/TEMP/botnetScanning/sshstuff.txt")
#targetG = TargetGoogle()
#targetMS = TargetMasscan("104.209.183.0/24","-p80")

SshBrute(target)
#osComerceExploit(target)
#osComerceExploit(targetG)
#osComerceExploit(targetMS)

target.runExploits()
#targetG.runExploits()
#targetMS.runExploits()
