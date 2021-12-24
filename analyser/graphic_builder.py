from matplotlib import pyplot as plt

import os;

# PARTICLE X Y Z ENERGY
DIR     = "./out/build/x64-Release/OUTPUT/CUSTOM/"
ODIR    = "./ANALYSER_OUTPUT/"

try:
    os.mkdir(ODIR)
except:
    pass

store = os.listdir(DIR)


def row(r):
    return (r[0], float(r[1]), float(r[2]), float(r[3]), float(r[4]))

def read_csv(filename):
    f = open(DIR+filename, "r")
    d = f.read().strip()
    if len(d) == 0:
        return None
    else:
        a = d.split("\n")
        b = list([row(x.split(";")) for x in a])
        return b

#print(sorted(store, key=lambda x: (float(x[3:11]), float( (x[14:16]).replace("m", "") ))) )


BASE_ENERGY = 1000
ENERGY_BY_POWER = {}
ENERGY_BY_PLATE = {}

ENERGY_ULTIMATE = {}

for CURRENT in sorted(store, key=lambda x: (float(x[3:11]), float( (x[14:17]).replace("m", "") ) ) ):
    CDATA = read_csv(CURRENT)
    s = {}

    #print(CDATA, CURRENT)

    if CDATA is not None:
        otd = ODIR + CURRENT + "/"

        try:
            os.mkdir(otd)
        except:
            pass
        
        E = 0

        for line in CDATA:     
            if line[0] not in s: s[line[0]] = 0
            s[line[0]] += 1
            E += line[-1]
        
        thisPower = float(CURRENT[3:11])*BASE_ENERGY # MeV Energy
        thisPlate = float((CURRENT[14:17]).replace("m", ""))

        if thisPower not in ENERGY_BY_POWER: ENERGY_BY_POWER[thisPower] = [
            [],[]
        ]
        if thisPlate not in ENERGY_BY_PLATE: ENERGY_BY_PLATE[thisPlate] = []
        if thisPower not in ENERGY_ULTIMATE: ENERGY_ULTIMATE[thisPower] = [
            [],[]
        ]

        ENERGY_BY_POWER[thisPower][0].append(thisPlate)
        ENERGY_BY_POWER[thisPower][1].append( (thisPower - E/100)/thisPower * 100 )

        ENERGY_ULTIMATE[thisPower][0].append(thisPlate)
        ENERGY_ULTIMATE[thisPower][1].append(E/100)
        '''
        fig, ax = plt.subplots()
        ax.set_title(CURRENT)
        ax.bar(s.keys(), list([s[i] for i in s.keys()]))
        plt.savefig( otd+"particles.png")
        '''

fig, ax = plt.subplots()
ax.set_title("Energy")
for i in ENERGY_BY_POWER:
    ax.plot( ENERGY_BY_POWER[i][0], ENERGY_BY_POWER[i][1],"-*", label=str(i)+"MeV")

plt.savefig( ODIR+"Energys.png")


fig, ax = plt.subplots()
ax.set_title("(Medium Energy on Detector by electron)")
for i in ENERGY_ULTIMATE:

    ax.plot( ENERGY_ULTIMATE[i][0], ENERGY_ULTIMATE[i][1],"-*", label=str(i)+"MeV")

    ax.axhline(i, color="r")

ax.set_xlabel("thickness, mm")
ax.set_ylabel("Energy hit the sensors MeV")
ax.legend()

plt.savefig( ODIR+"EnergysByPlate.png")