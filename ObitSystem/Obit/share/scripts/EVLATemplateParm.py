# Template project parameter file EVLAPipe
# Generate parameter file using EVLACal.EVLAMakeParmFile
#
# Substitutions surrounded by 'at' characters
# PROJECT     Project name (up to 12 char)
# SESSION     Session code
# BAND        Band code
# VLAFREQ     Frequency in Hz
# VLACFG      VLA configuraton ("A", "B", "CnD"...)
# DATAROOT    Root of archive data directory
# CONFIG      Configuration
# SELCHAN     Number of channels for selected configuration
# CALINT      CL table interval in min
# DOHANN      True or False if Hanning wanted
# DOSHAD      True or False if Shadow flagging wanted
# BPCAL       Bandpass calibrator list
# PHSCAL      Phase calibrator list
# AMPCAL      Amplitude calibrator list
# DLYCAL      Delay calibrator list
# PINCAL      Instrumental polarization calibrator list
# PRLCAL      R-L phase and delay calibrator
# PRLPHS      R-L phase for PRLCAL @ 1 GHz
# PRLRM       Rotation measure for PRLCAL
# REFANT      Reference antenna
# PLOTSRC     Diagnostic plot source name or None
# PLOTTIIME   Diagnostic plot timerange
# TARGET      List of target sources

# DESTDIR     Output directory 
# ARCHFILEID  Archive file ID
#--------------------------------------------------------------------------------------------
# Project specific parameter values for EVLAPipeline
project       = "@PROJECT@"           # Project name (12 char or less, used as AIPS Name)
session       = "@SESSION@"           # Project session code
band          = "@BAND@"              # Observing band
dataClass     = band+"Band"           # AIPS class of raw uv data
logFile       = project+"_"+session+"_"+band+".log"  # Processing log file
VLAFreq       = @VLAFREQ@             # Representive frequency
VLACfg        = @VLACFG@              # VLA configuraton ("A", "B", "CnD"...)

# Archive parameters
doLoadArchive = True       # Load from archive?
archRoot      = @DATAROOT@ # Root of ASDM/BDF data
selBand       = @BAND@     # Selected band, def = first  
selConfig     = @CONFIG@   # Selected frequency config, def = first  
selNIF        = 0          # Selected number of IFs, def = first  
selChan       = @SELCHAN@  # Selected number of channels, def = first  
calInt        = @CALINT@   # Calibration table interval in min.

# Calibration sources/models
parms["BPCal"]       = @BPCAL@      # Bandpass calibrator

# Hanning
doHann       = @DOHANN@

parms["doFD1"]       = True         # Do initial frequency domain flagging
parms["FD1widMW"]    = 31           # Width of the initial FD median window
parms["FD1maxRes"]   = 5.0          # Clipping level in sigma
parms["FD1TimeAvg"]  = 1.0          # time averaging in min. for initial FD flagging

parms["doMedn"]      = True         # Median editing?
parms["mednSigma"]   = 5.0          # Median sigma clipping level
parms["timeWind"]    = 1.0          # Median window width in min for median flagging
parms["avgTime"]     = 10.0/60.     # Averaging time in min
parms["avgFreq"]     = 0            # 1=>avg chAvg chans, 2=>avg all chan, 3=> avg chan and IFs
parms["chAvg"]       = 1            # number of channels to average

parms["doRMSAvg"]    = True         # Edit calibrators by RMSAvg?
parms["RMSAvg"]      = 3.0          # AutoFlag Max RMS/Avg for time domain RMS filtering
parms["RMSTimeAvg"]  = 1.0          # AutoFlag time averaging in min.

# Special editing list
doEditList  = False        # Edit using editList?
editFG      = 2            # Table to apply edit list to
# Channel numbers after Hanning if any
editList = [
    #{"timer":("0/00:00:0.0","5/00:00:0.0"),"Ant":[ 1,0],"IFs":[1,0],"Chans":[1,0],  "Stokes":'1111',"Reason":"No Rcvr"},
    ]

from EVLACal import EVLACalModel,EVLAStdModel
# Bandpass Calibration
calist = @BPCAL@
BPCals = []
for cal in calist:
    BPCals.append(EVLACalModel(cal))
# Check for standard model
EVLAStdModel(BPCals)
parms["BPCals"]       = BPCals      # Bandpass calibrator(s)

# Amp/phase calibration
calist = @PHSCAL@
PCals = []
for cal in calist:
    PCals.append(EVLACalModel(cal))
# Check for standard model
EVLAStdModel(PCals)
parms["PCals"]          = PCals   # Phase calibrator(s)

calist = @AMPCAL@
ACals = []
for cal in calist:
    ACals.append(EVLACalModel(cal))
# Check for standard model
EVLAStdModel(ACals)
parms["ACals"]          = ACals  # Amplitude calibrators

calist = @DLYCAL@
DCals = []
for cal in calist:
    DCals.append(EVLACalModel(cal))
# Check for standard model
EVLAStdModel(DCals)
parms["DCal"]          = DCals      # delay calibrators

parms["refAnt"]        = @REFANT@   # Reference antenna

# Sample spectra
parms["plotSource"]    = @PLOTSRC@        # Source name or None
parms["plotTime"]      = @PLOTTIME@       # timerange
parms["doRawSpecPlot"] = @PLOTSRC@!=None  # Plot Raw spectrum
parms["doSpecPlot"]    = @PLOTSRC@!=None  # Plot spectrum at various stages of processing

# Poln  Cal
parms["PCInsCals"]     = @PINCAL@  # List of instrumental poln calibrators

# R-L phase/delay calibration
parms["RLPCal"]    = @PRLCAL@     # Polarization angle (R-L phase) calibrator
parms["PCRLPhase"] = @PRLPHS@     # R-L phase difference for RLPCal
parms["RM"]        = @PRLRM@      # rotation measure (rad/m^2) for RLPCal
parms["RLDCal"]    = [(@PRLCAL@, @PRLPHS@, @PRLRM@)]     #  R-L delay calibrator, R-L phase, RM
parms["rlrefAnt"]  = @REFANT@     # Reference antenna REQUIRED

# Imaging
parms["targets"] = @TARGET@     # targets, empty = all
parms["Stokes"]  = "I"          # Stokes to image

# Control
T   = True
F   = False
check                  = F        # Only check script, don't execute tasks
debug                  = F        # run tasks debug
doLoadArchive          = T        # Load from archive?
parms["doHann"]        = @DOHANN@ # Hanning smooth?
parms["doClearTab"]    = T        # Clear cal/edit tables
parms["doCopyFG"]      = T        # Copy FG 1 to FG 2
parms["doQuack"]       = T        # Quack data?
parms["doShadow"]      = @DOSHAD@ # Flag shadowed data?
parms["doMedn"]        = T        # Median editing?
parms["doFD1"]         = T        # Do initial frequency domain flagging
parms["doRMSAvg"]      = T        # Do RMS/Mean editing for calibrators
parms["doPACor"]       = T        # Polarization angle correction?
parms["doDelayCal"]    = T        # Group Delay calibration?
parms["doBPCal"]       = T        # Determine Bandpass calibration
parms["doAmpPhaseCal"] = T        # Amplitude/phase calibration
parms["doAutoFlag"]    = T        # Autoflag editing after final calibration?
parms["doRecal"]       = T        # Redo calibration after editing
parms["doDelayCal2"]   = T        # Group Delay calibration of averaged data?, 2nd pass
parms["doBPCal2"]      = T        # Determine Bandpass calibration, 2nd pass
parms["doAmpPhaseCal2"]= T        # Amplitude/phase calibration, 2nd pass
parms["doAutoFlag2"]   = T        # Autoflag editing after final calibration?
parms["doCalAvg"]      = T        # calibrate and average data
parms["doRLDelay"]     = F        # Determine R-L delay?
parms["doPolCal"]      = F        # Do polarization calibration?
parms["doRLCal"]       = F        # Determine  R-L bandpass?
parms["doImage"]       = T        # Image targets
parms["doSaveImg"]     = T        # Save results to FITS
parms["doSaveUV"]      = T        # Save calibrated UV data to FITS
parms["doSaveTab"]     = T        # Save UV tables to FITS
parms["doKntrPlots"]   = T        # Contour plots
parms["doDiagPlots"]   = T        # Source diagnostic plots
parms["doMetadata"]    = T        # Generate metadata dictionaries
parms["doHTML"]        = T        # Generate HTML report
parms["doVOTable"]     = T        # VOTable report
parms["doCleanup"]     = T        # Destroy AIPS files

# diagnostics
parms["doSNPlot"]      = T        # Plot SN tables etc
parms["doRawSpecPlot"] = T        # Plot sample raw spectra?
parms["doSpecPlot"]    = T        # Plot sample calibrated/edited spectra?
parms["doReport"]      = T        # Individual source report