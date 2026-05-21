# Clinic Diagnostic Tool (CDT) — User Guide

> **Author:** Zackary Fleenor &nbsp;|&nbsp; **Revision:** v8 (April 2026)

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [Prerequisites](#2-prerequisites)
   - 2.1 [Software Requirements](#21-software-requirements)
   - 2.2 [C2000Ware CDT Install Path](#22-c2000ware-cdt-install-path)
   - 2.3 [Supported Devices](#23-supported-devices)
3. [Gen2 vs Gen3 Architecture Differences](#3-gen2-vs-gen3-architecture-differences)
4. [Export Communication Modes](#4-export-communication-modes)
   - 4.1 [Output Formats](#41-output-formats)
5. [Setting Up CDT — New Project](#5-setting-up-cdt--new-project)
6. [Setting Up CDT — Existing Project](#6-setting-up-cdt--existing-project)
7. [The CDT Interface](#7-the-cdt-interface)
   - 7.1 [Panel Overview](#71-panel-overview)
   - 7.2 [LED Indicator Legend](#72-led-indicator-legend)
   - 7.3 [Update Controls](#73-update-controls)
   - 7.4 [Save Registers](#74-save-registers)
   - 7.5 [Target State Card](#75-target-state-card)
   - 7.6 [Connections Panel](#76-connections-panel)
   - 7.7 [Debug Log Panel](#77-debug-log-panel)
8. [Diagnostic Workflows](#8-diagnostic-workflows)
9. [Diagnostic Panels — Complete Reference](#9-diagnostic-panels--complete-reference)
   - 9.1 [Clocking Panel](#91-clocking-panel)
   - 9.2 [Errata Panel](#92-errata-panel--advisory-coverage)
   - 9.3 [ADC Panel](#93-adc-panel)
   - 9.4 [GPIO Panel](#94-gpio-panel-gen3)
   - 9.5 [Interrupt Panel — PIE Group Reference](#95-interrupt-panel-gen3--pie-group-reference)
   - 9.6 [Peripheral Export Modules](#96-peripheral-export-modules)
   - 9.7 [CPU Timer Panel](#97-cpu-timer-panel)
10. [Device-Specific Notes](#10-device-specific-notes)
11. [Troubleshooting](#11-troubleshooting)
12. [Customising CDT](#12-customising-cdt)
13. [Frequently Asked Questions](#13-frequently-asked-questions)
14. [Additional Resources](#14-additional-resources)

---

## 1. Introduction

The **Clinic Diagnostic Tool (CDT)** is a GUI-based runtime diagnostic plugin for TI C2000™ microcontrollers. It integrates into Code Composer Studio (CCS) through MCU Mission Control / GUI Composer and uses **JTAG to read device registers without firmware modification**.

CDT instantly shows:

- **Clock configuration and PLL health** — with pass/fail range checks
- **Errata advisory status** with hyperlinks to TI errata documents
- **ADC** power, busy-state, and reference voltage per module (A–E)
- **GPIO** pin states, directions, mux values, and live toggle for outputs (ports A–H)
- **CPU Timer state:** running/stopped, interrupt flag, period, and prescale per timer
- **Peripheral error flags:** CAN, MCAN, SCI, SPI, I2C, LIN, CMPSS, FSI, CLB
- **PIE interrupt group status** — enabled and pending counts per group
- **Target state** (Running/Halted) with current PC address

**Ideal for:** bring-up engineers, application developers, field support, and production test.

> **No firmware changes required.** CDT reads all registers via non-intrusive JTAG data access — the target is not halted and your application code is untouched.

---

## 2. Prerequisites

### 2.1 Software Requirements

| Software | Min Version | Notes |
|----------|-------------|-------|
| Code Composer Studio | 20.4.x | Includes GUI Composer and MCU Mission Control |
| C2000Ware | 6.x | CDT lives in `utilities/transfer/.meta/` |
| SysConfig | 1.26+ | Bundled with CCS; processes CDT templates at build time |

### 2.2 C2000Ware CDT Install Path

CDT source lives at:

```
C:\ti\c2000\C2000Ware_X_XX_XX_XX\utilities\transfer\.meta\
```

| Subfolder | Contents |
|-----------|----------|
| `clinic/f28x/` | Clocking and errata clinic checks; device constants |
| `export/` | Export framework and per-peripheral JavaScript modules |
| `gui/` | GUI Composer HTML/JS templates (`index.gui.xdt`, `index.js.xdt`) |
| `exporter.js` | Export transport layer (SCI, SPI, USB, FSI, debugger) |
| `gui.js` | GUI module loader |

> **Never edit the installed C2000Ware files directly.** Make all changes in your development copy, then deploy with `sync_cdt_to_c2000ware.bat`. C2000Ware updates will overwrite `C:\ti\c2000\` directly.

### 2.3 Supported Devices

CDT supports all **15 C2000 devices** across two generations:

| Generation | Device | Max SYSCLK | GPIO Pins | LaunchPad / Hardware |
|------------|--------|-----------|-----------|----------------------|
| Gen2 | F2802x | 40 MHz | 26 | LAUNCHXL-F28027F |
| Gen2 | F2803x | 60 MHz | 41 | LAUNCHXL-F28035 |
| Gen2 | F2805x | 60 MHz | 40 | controlCARD-F28055 (no standalone LaunchPad) |
| Gen2 | F2806x | 90 MHz | 59 | LAUNCHXL-F28069M |
| Gen3 | F280013x | 120 MHz | 26 | LAUNCHXL-F2800137 |
| Gen3 | F280015x | 120 MHz | 42 | LAUNCHXL-F2800157 |
| Gen3 | F28002x | 100 MHz | 24 | LAUNCHXL-F280025C |
| Gen3 | F28003x | 120 MHz | 62 | LAUNCHXL-F280039C |
| Gen3 | F28004x | 100 MHz | 40 | LAUNCHXL-F280049C |
| Gen3 | F2807x | 120 MHz | 64 | controlCARD-F28075 |
| Gen3 | F2837xD | 200 MHz | 169 | LAUNCHXL-F28379D (dual-core) |
| Gen3 | F2837xS | 200 MHz | 169 | controlCARD-F28377S (single-core) |
| Gen3 | F2838x | 200 MHz | 169 | LAUNCHXL-F2838x |
| Gen3 | F28P55x | 150 MHz | 72 | LAUNCHXL-F28P55X |
| Gen3 | F28P65x | 200 MHz | 169 | LAUNCHXL-F28P65X |

> **Debug Probe:** All C2000 LaunchPads include an onboard **XDS110** debug probe over USB — no external emulator needed. Any XDS probe (XDS110, XDS200, XDS560) with JTAG connectivity works on custom boards.

---

## 3. Gen2 vs Gen3 Architecture Differences

CDT supports two hardware generations with fundamentally different register architectures. Understanding the differences helps interpret CDT output correctly.

| Aspect | Gen2 (F2802x / F2803x / F2805x / F2806x) | Gen3 (all others) |
|--------|-------------------------------------------|-------------------|
| **PLL Registers** | `SysCtrlRegs.PLLCR` / `PLLSTS` | `ClkCfgRegs.SYSPLLMULT` and related |
| **PLL Formula** | `SYSCLK = OSCCLK × DIV / DIVSEL`<br>(DIVSEL: 0,1=÷4; 2=÷2; 3=÷1) | REFDIV/ODIV or FMULT depending on device (see Section 9.1.2) |
| **ADC Prescale** | `CLKDIV2EN` / `CLKDIV4EN` bits (÷1, ÷2, ÷4 only) | `PRESCALE` register (integer or half-step depending on device) |
| **ADC Clock Max** | 25 MHz | 60 MHz |
| **ADC Register Base** | `AdcRegs` (single instance) | `AdcaRegs`, `AdcbRegs`, `AdccRegs`… |
| **HRPWM Min Clock** | 40 MHz (MEP calibration) | 60 MHz (SFO v8 calibration) |
| **Max SYSCLK** | 40–90 MHz (device-dependent) | 100–200 MHz (device-dependent) |
| **GPIO Ports** | Ports A–B only | Ports A–H (device-dependent) |
| **CAN** | eCAN (legacy CAN 2.0) | DCAN and/or MCAN (CAN-FD) |
| **CDT Clocking Path** | Reads `SysCtrlRegs`; formula: `OSCCLK × DIV / DIVSEL` | Reads `ClkCfgRegs`; computes via REFDIV/ODIV or FMULT |

> **Gen2 ADC Prescale:** Gen2 ADC prescale is configured via `CLKDIV2EN` and `CLKDIV4EN` bits in `AdcRegs`, giving only three divider options (÷1, ÷2, ÷4). The maximum ADCCLK is approximately 25 MHz. CDT will show a **RED LED** if ADCCLK exceeds this limit.

---

## 4. Export Communication Modes

CDT supports multiple methods to transport diagnostic data from the target to the host PC. The mode is selected in SysConfig under **Clinic — Device Diagnostic Export Mode**.

| Mode | Transport | When to Use | Notes |
|------|-----------|-------------|-------|
| **Debugger (Recommended)** | JTAG / XDS probe | All development and debugging | No UART/SPI wiring needed; output appears in CDT GUI. Works on all devices. |
| **SCI (UART)** | UART TX/RX pins | Production environments without JTAG, or noisy motor-control systems | Default for C28x. Requires SCI peripheral configured in SysConfig. |

> **Debugger Mode for Development:** Use "Use debugger for device diagnostic export" during development. It requires no external wiring and data appears directly in the CDT GUI. Switch to SCI only for noise-sensitive or production scenarios.

### 4.1 Output Formats

| Format | Description | Best For |
|--------|-------------|----------|
| **JSON** (default) | Structured key-value pairs, human-readable | Offline analysis, support tickets, automation |
| **CSV** | Comma-separated flat table | Spreadsheet import, data logging |

---

## 5. Setting Up CDT — New Project

### Step 1: Import the Transfer Example

```
<C2000WARE_INSTALL>\driverlib\<device>\examples\transfer_ex1_customlog_export_sci
```

In CCS: **Project > Import CCS Projects…**  
Browse to the example folder, select the project, click **Finish**.

### Step 2: Set `GUI_SUPPORT = 1`

1. Right-click the project > **Project Properties**.
2. Under **General > Variables**, click `GUI_SUPPORT`.
3. Set the **Value** to `1` and click **OK > Save and Close**.

> **If `GUI_SUPPORT` is 0 (default)**, the CDT GUI template is not generated during build and the plugin will never appear in CCS.

### Step 3: Configure CDT in SysConfig

1. Double-click the `.syscfg` file to open SysConfig.
2. Under **MCU Mission Control and Transfer**, enable **MCU Mission Control**.
3. Set **Clinic — Device Diagnostic Export Mode** to **Use debugger for device diagnostic export**.
4. Enable **Custom Export Logger**.
5. *(Optional)* Set **GUI Project Name** — this becomes the plugin name in CCS.
6. Save the `.syscfg` file.

> **Default State:** MCU Mission Control and Custom Export Logger are already enabled in a fresh transfer example. You only need to confirm the export mode selection.

### Step 4: Add Peripherals to SysConfig (Critical)

CDT only shows a panel for a peripheral when that peripheral is **configured in SysConfig**. Before running CDT, add each peripheral you want to diagnose:

| To see this CDT panel… | Add this to SysConfig |
|------------------------|----------------------|
| ADC A / B / C / D / E | Add ADC module; select instance (ADCA, ADCB…) |
| CAN / DCAN | Add CAN module; select instance A or B |
| MCAN (CAN-FD) | Add MCAN module |
| SCI (UART) | Add SCI module; select instance A/B/C/D |
| SPI | Add SPI module; select instance |
| I2C | Add I2C module |
| LIN | Add LIN module |
| CMPSS | Add CMPSS module; select instance |
| FSI TX / RX | Add `FSI_TX` or `FSI_RX` module |
| CLB | Add CLB module; select tile |
| CPU Timer 0 / 1 / 2 | Add CPUTIMER module; select instance (0, 1, or 2) |

### Step 5: Build

**Project > Clean**, then **Project > Build All**. Verify no SysConfig errors in the build log.

### Step 6: Start Debug Session

1. Click the green **Debug** button (**F11**).
2. Wait for target connection and program load.
3. Press **F8** to run. **Application must be running** for CDT to read registers.

> **Missing Panel?** If a peripheral does not appear in CDT, it is almost always because it is not added in SysConfig. Add the module, rebuild, and run **Refresh Plugins**.

### Step 7: Launch CDT

1. Open **Command Palette** (`Ctrl+Shift+P`).
2. Run **Refresh Plugins**.
3. Select **View > Plugins** and choose the Clinic Tool by name.

### Step 8: Verify Connection and Click Update

1. Open the **Connections** section — verify the LED shows "Hardware connected."
2. Click **Update All** to populate every panel with live register data.

---

## 6. Setting Up CDT — Existing Project

1. Set `GUI_SUPPORT = 1` (**Project Properties > General > Variables**).
2. Open the `.syscfg` file.
3. Enable **MCU Mission Control**.
4. Set export mode to **Use debugger for device diagnostic export**.
5. Enable **Custom Export Logger**.
6. Add any peripherals you want to diagnose (see [Step 4](#step-4-add-peripherals-to-sysconfig-critical) above).
7. **Clean Build**, then **Command Palette > Refresh Plugins > View > Plugins**.

> **Always run Refresh Plugins after every build.** CCS does not detect new GUI templates automatically.

> **Peripherals Only Show If Configured:** CDT reflects your SysConfig exactly. A peripheral that is disabled or absent in SysConfig will have no CDT panel, even if the peripheral is physically present on the device.

---

## 7. The CDT Interface

### 7.1 Panel Overview

| Tab | What It Shows | Gen2 | Gen3 |
|-----|--------------|------|------|
| **System** | Device ID, SYSCLK summary, Target State card (Running/Halted + PC) | ✅ | ✅ |
| **Clocking** | Full PLL chain, all derived clocks, pass/fail checks | ✅ | ✅ |
| **Errata** | Device-specific advisory checks with errata doc hyperlinks | ✅ | ✅ |
| **ADC** | Power, busy flag, reference voltage per ADC module (A–E) | ✅ | ✅ |
| **GPIO** | Port A–H pin states, direction, mux, toggle for outputs | — | ✅ |
| **Interrupt** | PIE group grid (12 groups), enabled/pending counts | — | ✅ |
| **CPU Timer** | Timer 0/1/2 running state, interrupt flag, period, live counter, and prescale | ✅ | ✅ |
| **Peripherals** | CAN/MCAN, SCI, SPI, I2C, LIN, CMPSS, FSI, CLB error flags | ✅ | ✅ |

### 7.2 LED Indicator Legend

| LED | Meaning | Action Required |
|-----|---------|-----------------|
| 🟢 **GREEN** | Value within specification — normal operation | None |
| 🔴 **RED** | Out of specification or error flag active | Hover for tooltip; check errata link if shown |
| ⚫ **GREY** | Not applicable for this device or no data read yet | Click Update or verify SysConfig |

### 7.3 Update Controls

- **Update** *(per panel)* — refreshes only that panel's registers
- **Update All** — refreshes every panel simultaneously
- **Auto Update toggle** — continuously polls at a configurable interval (set the interval in the field beside the toggle)

All reads use **non-intrusive JTAG data access** — the target is not halted.

### 7.4 Save Registers

Each peripheral panel has a **Save Registers** button that snapshots all register values for that peripheral. Use it to:

- Capture state immediately before or after a fault
- Attach a register dump to a support ticket
- Compare state across multiple runs offline

> **Volatile Registers Are Skipped:** CDT skips certain registers during export to avoid side effects: `RESULT` registers (change per-conversion), `FLAGCLR` registers (write-1-to-clear — reading is destructive), and `FORCE` registers (write-only triggers). If a register you expect is missing from a save, it is likely in one of these categories.

### 7.5 Target State Card

- 🟢 **GREEN — RUNNING** — device executing code; PC shows "(running)"
- 🔴 **RED — HALTED** — at a breakpoint; current PC address displayed

### 7.6 Connections Panel

Shows real-time XDS JTAG link status. **Green LED + "Hardware connected"** = probe active. Errors are logged here for troubleshooting.

### 7.7 Debug Log Panel

Click the **Debug** button (bottom-right) to open a resizable scrolling log of all register operations. Drag the left edge to resize. Useful when values appear incorrect or missing.

---

## 8. Diagnostic Workflows

### 8.1 Verify Clock Configuration After Hardware Bring-Up

1. Connect board, build, debug, press **F8** to run.
2. Open the **Clocking** tab and click **Update**.
3. Verify SYSCLK matches your target frequency.
4. **All GREEN LEDs** = clocking within specification.
5. **RED LED** = violated limit. Hover for the exact constraint.
6. Click the errata hyperlink (if shown) for advisory guidance.

> **Clock Shows 0?** `Device_init()` PLL configuration has not run. Set a breakpoint after the PLL init call, resume to it, then click Update. Also verify the XTAL frequency in SysConfig matches the board crystal.

### 8.2 Check Errata Compliance

1. Open **Errata** tab > click **Update**.
2. Only relevant checks for your device are shown — irrelevant ones are hidden.
3. **RED LED** = current register state matches an errata advisory.
4. Click the errata name (hyperlink) to open the TI errata document at the relevant section.
5. Apply the recommended workaround and re-run.

> **RED Errata LED = Register State Matches Advisory.** It is a diagnostic indicator, not a definitive failure. Refer to the TI errata document to determine actual impact.

### 8.3 Diagnose CAN / MCAN Bus Issues

1. Open **Peripherals** tab; select **CAN** or **MCAN**.
2. Choose the instance from the dropdown (CANA / CANB for DCAN; MCANA / MCANB for MCAN-FD).
3. Click **Update**.
4. Check LEDs: 🔴 **BOff** = bus-off; **EWarn** = warning threshold; **EPass** = error-passive; **PER** = protocol error.
5. For MCAN also check RX FIFO overflow and ECC SBE/DBE LEDs.
6. Use **Save Registers** to capture the full CAN register state.

> **F28P55x MCAN Note:** F28P55x uses **AUXCLKIN** (an external clock input pin) as the MCAN bit clock source — unlike all other MCAN devices which derive the clock from the internal PLL or AUXPLL. CDT cannot auto-calculate the MCAN clock frequency for F28P55x; the value is board-defined. Verify the AUXCLKIN frequency matches your MCAN bit timing requirements.

### 8.4 Diagnose Peripheral Errors (General)

1. Open the tab for the peripheral (SCI, SPI, I2C, LIN, CMPSS, FSI, CLB).
2. Select the instance from the dropdown.
3. Click **Update**. 🔴 RED LEDs indicate active error flags.
4. Hover each RED LED for a description of the error condition.
5. Use **Save Registers** for a full register snapshot.

### 8.5 HRPWM / MEP Calibration Check

High-Resolution PWM (HRPWM) requires a minimum clock for the Micro Edge Positioning (MEP) calibration run by the Scale Factor Optimizer (SFO) library.

| Generation | Min HRPWMCLK for SFO | Notes |
|------------|----------------------|-------|
| Gen2 (F2802x, F2803x, F2805x, F2806x) | **40 MHz minimum** | HRPWMCLK = SYSCLK on Gen2 |
| Gen3 (all others) | **60 MHz minimum** | SFO v8; HRPWMCLK derived from SYSCLK |

1. In CDT **Clocking** tab, check the **HRPWMCLK** row.
2. A 🔴 RED LED means HRPWMCLK is below the SFO minimum — MEP calibration will fail or be inaccurate.
3. Increase SYSCLK to bring HRPWMCLK above the minimum for your generation.
4. Re-run your firmware's SFO calibration call (typically in a background loop) after correcting the clock.

> **SFO Background Calibration:** SFO runs continuously in the background of most HRPWM examples. A HRPWMCLK check that passes in CDT means the hardware supports MEP calibration. The accuracy of MEP calibration also degrades with temperature — re-run SFO periodically.

### 8.6 Verify CPU Timer Configuration and State

All three C2000 CPU timers (TIMER0, TIMER1, TIMER2) are 32-bit down-counters with a 16-bit prescaler clocked from SYSCLK. CDT shows both configuration and live state in real time.

1. Add the **CPUTIMER** module in SysConfig for each timer instance you want to diagnose; rebuild and Refresh Plugins.
2. Open the **CPU Timer** panel; select the instance from the dropdown (TIMER0, TIMER1, TIMER2).
3. Click **Update**. Check the **Timer Running** LED — 🔴 RED means the timer is actively counting.
4. Verify **Period (PRD)** and **Prescale (TDDR / TDDRH)** match your firmware configuration. The effective timer frequency is:
   ```
   Timer frequency = SYSCLK / ((PRD + 1) × (Prescale + 1))
   ```
5. If **Interrupt Flag (TIF)** stays RED while the device is running, the ISR is not clearing the flag — check that `CpuTimer0Regs.TCR.TIF = 1` is being written in the ISR.
6. Check the **Free Run** and **Soft Stop** LEDs to understand how the timer behaves when the debugger halts the CPU:
   - 🟢 **Free Run = ON:** Timer keeps counting through breakpoints — ISRs may fire during step-through.
   - ⚫ **Free Run = OFF:** Timer stops on halt — predictable step-through behaviour.

### 8.7 Real-Time Monitoring with Auto-Update

1. Enable the **Auto Update** toggle at the top of CDT.
2. Set the poll interval in the adjacent field (seconds).
3. CDT continuously refreshes all visible panels while your firmware runs.
4. Use this mode to observe clocks or error flags changing during dynamic load.

---

## 9. Diagnostic Panels — Complete Reference

### 9.1 Clocking Panel

| Clock | Description | Valid Range |
|-------|-------------|-------------|
| **OSCCLK** | Input oscillator (crystal or internal OSC) | Typically 10 or 20 MHz |
| **PLLRAWCLK** | VCO output before output dividers (Gen3 only) | 6–240 MHz |
| **VCOCLK** | Internal VCO before ODIV (Gen3 REFDIV/ODIV only) | 220–600 MHz |
| **PLLSYSCLK** | Post-divider PLL output | Up to device max |
| **SYSCLK** | Final CPU clock (after SYSCLKDIVSEL) | See table below |
| **LSPCLK** | Low-speed peripheral clock (SCI, SPI, I2C) | 2 MHz – SYSCLK |
| **ADCCLK** | ADC clock (shared across all ADC modules) | 5–60 MHz (Gen3) / 2–25 MHz (Gen2) |
| **HRPWMCLK** | HRPWM / SFO MEP calibration clock | ≥60 MHz Gen3 / ≥40 MHz Gen2 |
| **CANCLK** | CAN bus clock (= SYSCLK, no dedicated divider) | ≥8 MHz for 1 Mbps operation |
| **MCANCLK** | CAN-FD clock (from AUXPLL or PLLCLK, device-dependent) | ≥20 MHz |
| **INTCLK** | Internal reference (OSCCLK / REFDIV; Gen3 REFDIV/ODIV only) | 2–20 MHz |

#### 9.1.1 Max SYSCLK by Device

| Device | Max SYSCLK |
|--------|-----------|
| F2802x | 40 MHz |
| F2803x, F2805x | 60 MHz |
| F2806x | 90 MHz |
| F28002x, F28004x | 100 MHz |
| F280013x, F280015x, F28003x, F2807x | 120 MHz |
| F28P55x | 150 MHz |
| F2837xD, F2837xS, F2838x, F28P65x | 200 MHz |

#### 9.1.2 PLL Architecture

| Type | Devices | Formula / Notes |
|------|---------|-----------------|
| **PLLCR/PLLSTS** (Gen2) | F2802x, F2803x, F2805x, F2806x | `SYSCLK = OSCCLK × DIV / DIVSEL`<br>DIVSEL: 0,1=÷4; 2=÷2; 3=÷1 (Ref: SPRS523 Table 7-9) |
| **REFDIV/ODIV** (Gen3) | F280013x, F280015x, F28002x, F28003x, F2838x, F28P55x, F28P65x | Standard Gen3 `ClkCfgRegs` formula |
| **FMULT** (Gen3) | F2807x, F2837xD, F2837xS | Uses fractional multiplier: `PLLRAWCLK = OSCCLK × (IMULT + FMULT)` |
| **FMULT+ODIV** (Gen3) | F28004x | Hybrid — has FMULT and ODIV but **no REFDIV**; ODIV uses +1 encoding (register value 0 = ÷1) |

> **MCAN Clock Sources by Device:**
> - **F2838x, F28P65x** — MCAN clocked from **AUXPLL** via `MCANCLKDIV` register
> - **F280015x, F28003x** — MCAN clocked from **PLLCLK** via `MCANCLKDIV` register
> - **F28P55x** — MCAN bit clock sourced from **AUXCLKIN** (external clock input pin); CDT cannot auto-calculate this frequency; it is board-defined

#### 9.1.3 ADC Prescale by Device

| Prescale Type | Devices | Divider Values |
|---------------|---------|----------------|
| **Binary** (Gen2) | F2802x, F2803x, F2805x, F2806x | ÷1, ÷2, ÷4 only (CLKDIV2EN/4EN bits) |
| **Integer ÷1–÷8** (Gen3) | F280013x, F280015x, F28002x, F28003x, F28004x | Register values 0,2,4,6,8,10,12,14 (value 1 reserved) |
| **Half-step ÷1–÷9** (Gen3) | F2807x, F2837xD/S, F2838x, F28P55x, F28P65x | Values 0,2,3,4,5,…16; formula: `(reg=0)→÷1`, `(reg=2)→÷2`, `(reg>2)→((reg−2)×0.5)+2` |

> **ADC Prescale Register:** Value `1` is reserved on all Gen3 devices (CDT returns NaN and shows a warning). Maximum valid register value is `16` (= ÷9 on half-step devices).

---

### 9.2 Errata Panel — Advisory Coverage

CDT checks each errata advisory against the current device register state. Only checks applicable to the connected device are shown.

| Advisory / Condition | Affected Devices | What CDT Checks |
|----------------------|-----------------|-----------------|
| **PLL DIVSEL Sequence** (Gen2) | F2802x, F2803x (SPRZ283); F2805x (SPRZ324); F2806x (SPRZ281) | DIVSEL must step through /4 → /2 → /1 after PLL lock |
| **Flash Pump Wakeup** | F2802x, F2803x (SPRZ283) | Flash pump wakeup delay register state |
| **ADC Reference Voltage** | F2805x (SPRZ324) | ADC reference voltage stability configuration |
| **I2C Clock Stretching** | F2806x (SPRZ281) | I2C open-drain buffer configuration |
| **ADC Fractional Divider** | F280013x, F280015x, F28002x, F28003x, F28004x | ADC clock prescale must be even (odd values degrade performance) |
| **CMPSS Latch Clear** | F28004x, F2807x, F2837xD/S, F28P55x | CMPSS comparator latch state (F2838x and F28P65x **not affected**) |
| **CMPSS Ramp Generator** | F2807x, F2837xD/S | Ramp generator COMPHLATCH state (F2838x and F28P65x **not affected**) |
| **ePWM Dead-Band** | F2807x, F2837xD/S | Dead-band shadow load mode with zero delay (F2838x and F28P65x **not affected**) |
| **Missing Clock Detect (MCD)** | F28P55x, F28P65x, F2838x | MCD enable + PLL enable — must not be simultaneously active |
| **Flash ECC** | F28P55x, F28P65x | Flash ECC enabled — single-bit error interrupt is **not** generated (must poll status) |
| **DCC Single-Shot** | F28004x, F28002x | Dual-Clock Comparator single-shot mode configuration |
| **SDFM Manchester Mode** | F28004x, F2807x, F2837xD/S | SDFM Manchester mode active (F2838x and F28P65x **not affected**) |
| **I2C Open-Drain Buffer** (Gen3) | F28004x, F2807x, F2837xD/S | I2C enabled in master mode — verify pull-up resistors (F2838x and F28P65x **not affected**) |
| **PLL Lock** | F28004x, F2807x, F2837xD/S | PLL lock status — may fail on first attempt; driverlib handles retry (F2838x and F28P65x **not affected**) |
| **FSI Overrun** | F28004x, F2838x | FSI RX overrun flag state |
| **eQEP Position Counter** | Most Gen3 except F28P65x | eQEP `PCRM` mode — must not be 0 (reset-on-index) |

---

### 9.3 ADC Panel

| Module | Devices | Indicators |
|--------|---------|------------|
| **ADCA** | All 15 devices | `adcPowerDown`: 🔴 RED if ADC powered off; `adcBusy`: 🔴 RED if busy flag stuck |
| **ADCB** | F28003x, F28004x, F2807x, F2837xD/S, F2838x, F28P55x, F28P65x | Same as ADCA |
| **ADCC** | All Gen3 except F2807x | Same as ADCA *(F2807x has ADCD instead of ADCC)* |
| **ADCD** | F2807x, F2837xD/S, F2838x, F28P55x | Same as ADCA *(F28P65x does NOT have ADCD — it has only ADCA/B/C)* |
| **ADCE** | **F28P55x only** | Same as ADCA — F28P55x is the only 5-ADC-module device in the CDT set |

> **F28P65x ADC Topology:** F28P65x has exactly **3 ADC modules: ADCA, ADCB, ADCC** — no ADCD, no ADCE. This was a deliberate hardware design choice for the device.

> **F28P55x ADC Topology:** F28P55x has all **5 ADC modules: ADCA, ADCB, ADCC, ADCD, ADCE** — the only C2000 device with ADCE.

---

### 9.4 GPIO Panel (Gen3)

| Port | GPIO Range | Available On | Notes |
|------|-----------|--------------|-------|
| **A** | GPIO 0–31 | All Gen3 | |
| **B** | GPIO 32–63 | All Gen3 | |
| **C** | GPIO 64–95 | F2807x, F2837xD/S, F2838x, F28P55x, F28P65x | |
| **D** | GPIO 96–127 | F2837xD/S, F2838x, F28P65x | |
| **E** | GPIO 128–159 | F2837xD/S, F2838x, F28P65x | |
| **F** | GPIO 160–168 | F2837xD/S, F2838x, F28P65x | GPIO 169–191 reserved; valid range ends at GPIO 168 |

Each pin cell shows: **value** (0/1), **direction** (IN/OUT), and **mux function**.

> GPIO panels are Gen3 only. Gen2 devices (F2802x–F2806x) have GPIO functionality but no dedicated CDT GPIO panel — check GPIO state via the System register exports.

---

### 9.5 Interrupt Panel (Gen3) — PIE Group Reference

The Interrupt panel shows the **12 PIE (Peripheral Interrupt Expansion) groups** with **enabled** and **pending** counts per group. CDT filters to show only what applies to the connected device.

| PIE Group | Key Interrupts |
|-----------|---------------|
| **Group 1** | ADCx SOC results, XINT1/2, Timer0, Wake |
| **Group 2** | ePWM Trip Zone: ePWM1_TZ – ePWM8_TZ |
| **Group 3** | ePWM period/event: ePWM1 – ePWM8 |
| **Group 4** | eCAP: ECAP1 – ECAP7 (device-dependent count) |
| **Group 5** | eQEP1–3, CLB1–4, SDFM1–2 |
| **Group 6** | SPI A/B/C RX and TX |
| **Group 7** | DMA CH1 – CH6 |
| **Group 8** | I2C A/B, LIN A/B, PMBUS A |
| **Group 9** | SCI A/B RX/TX, CAN A/B RX/TX |
| **Group 10** | ADC Events: ADCA–ADCD (device-dependent) |
| **Group 11** | CLA: CLA1_1 – CLA1_8 |
| **Group 12** | XINT3–5, FPU overflow/underflow, Flash single-bit ECC, Timer1, Timer2 |

> **Using the Interrupt Panel:** A non-zero **Pending** count in a PIE group means at least one interrupt in that group is waiting to be serviced. If the count keeps growing while the device is halted, check the corresponding peripheral for an error condition.

---

### 9.6 Peripheral Export Modules

| Peripheral | LEDs | Key Indicators | Instance Dropdown |
|------------|------|----------------|-------------------|
| **CAN (DCAN)** | 4 | Bus-Off (BOff), Error-Warning (EWarn), Error-Passive (EPass), Protocol Error (PER) | CANA, CANB |
| **MCAN (CAN-FD)** | 12 | Bus-Off, EW, EP, RF0L/RF1L FIFO overflows, MRAF, ECC SBE/DBE, SBE/DBE interrupt | MCANA, MCANB |
| **SCI (UART)** | 9 | Framing (FE), Parity (PE), Overrun (OE), RX Ready (RXRDY), TX Ready (TXRDY), Break (BRKDT), RX FIFO overflow (RXFFOVF), TX empty, RX error any | SCIA–SCID |
| **SPI** | 6 | RX overrun (RXOVF), TX full, FIFO TX/RX flags, parity, SPIBUSY | SPIA–SPID |
| **I2C** | 11 | Arbitration lost, NACK, No-Ack, Bus Busy, Stop condition, Start condition, SCL low, SDA low, TX empty, RX full, module busy | I2CA, I2CB |
| **LIN** | 14 | Bit error, bus error, checksum error, framing error, NRE timeout, parity, break detect, sync field error, FE timeout, bus stuck, TXn/RXn FIFO overflow, IOBUSF, module error | LINA, LINB |
| **CMPSS** | 4 | `compHigh`, `compHighLatch`, `compLow`, `compLowLatch` | Per tile instance |
| **FSI TX** | 2 | TX buffer overrun (TXBUFOVERRUN), TX buffer underrun (TXBUFUNDERRUN) | FSITXA, FSITXB |
| **FSI RX** | 8 | RX error tag mismatch (RXERRTAGMATCH), frame overrun (RXFRAMEOVERRUN), error frame (RXERRFRAME), buf underrun (RXBUFUNDERRUN), buf overrun (RXBUFOVERRUN), EOF error (RXEOFERR), type error (RXTYPEERR), CRC error (RXCRCERR) | FSIRXA, FSIRXB |
| **CLB** | 8 | CLB tile logic output states (OUT0–OUT7 per tile) | CLB1–CLB8 |
| **CPU Timer** | 6 LEDs + 5 values | See Section 9.7 | TIMER0, TIMER1, TIMER2 |

---

### 9.7 CPU Timer Panel

All C2000 devices — Gen2 and Gen3 — have **three CPU timers (TIMER0, TIMER1, TIMER2)**. Each is a 32-bit down-counter with a 16-bit prescaler clocked from SYSCLK.

> **SysConfig required:** Add a `CPUTIMER` module instance in SysConfig for each timer you want to diagnose. CDT will show a separate panel per instance.

#### Architecture

```
SYSCLK → [÷ (Prescale + 1)] → Prescale Counter (PSC)
                              ↓ (on underflow)
                         Timer Counter (TIM) counts down from PRD
                              ↓ (on TIM = 0)
                         TIM reloads from PRD  +  TIF flag set
                                               +  CPU interrupt (if TIE=1)
```

- **Timer frequency** = `SYSCLK / ((PRD + 1) × (Prescale + 1))`
- **Full prescale** = `(TDDRH << 8) | TDDR` (16-bit combined value)

#### LED Indicators

| LED | Register Bit | Meaning when RED |
|-----|-------------|-----------------|
| **Timer Running** | `TCR.TSS = 0` | Timer is actively counting down |
| **Interrupt Enabled** | `TCR.TIE = 1` | Timer will generate an interrupt on underflow |
| **Interrupt Flag (TIF)** | `TCR.TIF = 1` | Timer reached zero — ISR should clear this; if stuck RED, ISR is not clearing TIF |
| **Reload Pending** | `TCR.TRB = 1` | Software-triggered reload in progress |
| **Free Run** | `TCR.FREE = 1` | Timer keeps counting when debugger halts CPU |
| **Soft Stop** | `TCR.SOFT = 1` | Timer stops after current decrement on halt (when FREE=0) |

#### Value Readouts

| Value | Register | Description |
|-------|----------|-------------|
| **Period (PRD)** | `PRD` | Reload value — timer counts from here to 0 |
| **Counter (TIM)** | `TIM` | Live count value — volatile, captured at read time |
| **Prescale Low (TDDR)** | `TPR.TDDR` | Low 8 bits of prescaler (0–255) |
| **Prescale High (TDDRH)** | `TPRH.TDDRH` | High 8 bits of prescaler (0–255) |
| **Prescale Counter (PSC)** | `TPR.PSC` | Current prescale count value (counts from TDDR to 0) |
| **Control Reg (TCR)** | `TCR` | Full control register for detailed analysis |

#### Debug-Mode Behaviour (FREE / SOFT Bits)

The **Free Run** and **Soft Stop** LEDs show how each timer is configured to behave when the debugger halts the CPU. If FREE=1 on a timer driving an RTOS tick, task timeouts may accumulate during step-through. Configure these bits in your firmware's timer initialisation to match your debug workflow.

---

## 10. Device-Specific Notes

| Device | Notes |
|--------|-------|
| **F2807x** | ADCD present but **NOT ADCC** — ADC panel shows instances A, B, D only |
| **F28P55x** | Only device with **ADCE** — ADC panel shows 5 modules (A–E). 72 GPIO pins. MCAN uses **AUXCLKIN** (external clock pin) — not derivable from registers |
| **F28004x** | **Hybrid PLL** (FMULT + ODIV, no REFDIV). ODIV register +1 encoding: value 0 means ÷1 |
| **F28P65x** | **ADC:** only ADCA, ADCB, ADCC — no ADCD, no ADCE. **CAN:** CANA (DCAN legacy) + MCANA/MCANB (CAN-FD) — no CANB. GPIO ports A–F (GPIO 0–168); 169 GPIO pins (Port F ends at GPIO 168) |
| **F2837xD** | **Dual-core:** CDT connects to CPU1 by default. CPU2 requires a separate CCS debug session |
| **F2837xS** | Single-core variant of F2837xD — same peripheral set but one CPU |
| **F2838x** | Full connectivity device: MCAN (CAN-FD) from AUXPLL, EtherCAT, 169 GPIO pins |
| **F2802x** | Gen2 — no eCAN, DMA, or CLA. Peripheral panel shows HRPWM and LIN only. 26 GPIO pins |
| **F2803x** | Gen2 — PLLCR/PLLSTS in SysCtrlRegs; CDT uses Gen2 clocking calculation path |
| **F2805x** | Gen2 — controlCARD form-factor only; no standalone LaunchPad. 40 GPIO pins |
| **F2806x** | Gen2 — highest Gen2 performance (90 MHz); includes USB peripheral. 59 GPIO pins |
| **F280013x** | Smallest Gen3 entry-level device: 26 GPIO pins, no CLB, no eCAN/MCAN. Flash size not in PARTIZL — CDT uses programmatic fallback |
| **F280015x** | Entry-level Gen3. Flash size not in PARTIZL — CDT uses programmatic fallback. Shares DEVICE_CLASS_ID 0x07 with F2807x; distinguished by PARTNO field |

---

## 11. Troubleshooting

| Symptom | Likely Cause | Resolution |
|---------|-------------|------------|
| CDT not in Plugins menu | Plugins not refreshed after build | **Command Palette > Refresh Plugins**, then **View > Plugins** |
| CDT GUI does not open | `GUI_SUPPORT=0` or SysConfig not configured | Set `GUI_SUPPORT=1`; enable MCU Mission Control + Custom Export Logger; Clean Build |
| All LEDs grey | Export mode wrong or debugger not connected | Set export mode to "Use debugger for device diagnostic export"; verify XDS connection in Connections panel |
| "Hardware connected" LED not lit | XDS probe not detected | Check USB cable; replug LaunchPad; restart CCS debug session |
| Peripheral panel missing | Peripheral not in SysConfig | Add the peripheral module in `.syscfg`; rebuild; Refresh Plugins |
| Clock values show 0 | `Device_init()` not run | Set breakpoint after PLL init; verify crystal frequency matches SysConfig oscillator setting |
| Error -2010 on debug connect | "Auto Run" enabled | Disable Auto Run: **Run > Debug Configurations > [your config] > Startup tab** |
| Wrong peripheral instance data | Instance name not resolved | Use `"myCAN_A"` / `"myCAN_B"` SysConfig naming to match export module letter mapping (`a→CanaRegs`, `b→CanbRegs`) |
| Register missing from Save Registers output | Volatile register (RESULT, FLAGCLR, or FORCE) | Expected — CDT skips registers with destructive read side effects |
| "Undefined" JavaScript errors | Syntax error in modified export module | Run `node --check export_mod_xxx.js`; review CCS SysConfig build log |
| GPIO values wrong or stale | Stale read or `Device_init` not complete | Click **Update** on GPIO tab; verify `Device_init` has run |
| ADC panel missing for some modules | ADC module not in SysConfig or device lacks that ADC | Add AdcX module in SysConfig; check ADC availability matrix in [Section 9.3](#93-adc-panel) |
| Interrupt panel shows all zeros | No interrupts enabled or device halted immediately | Verify ISRs are enabled in firmware; run to a point in main loop; click Update |
| MCAN panel empty | Device does not have MCAN (DCAN only) | Verify device supports MCAN — only F280015x, F28003x, F2838x, F28P55x, F28P65x |
| CPU Timer TIF flag stuck RED | ISR not clearing interrupt flag | Ensure ISR writes `CpuTimer0Regs.TCR.bit.TIF = 1` (write-1-to-clear); verify ISR is enabled and PIE ACK is issued |

---

## 12. Customising CDT

Export modules are JavaScript files in:

```
C:\ti\c2000\C2000Ware_X_XX_XX_XX\utilities\transfer\.meta\export\mods\export_mod_*.js
```

### 12.1 Adding a Custom Indicator to a Peripheral Module

Extend the `exportsInfo` array with a new entry:

```javascript
{
    name: "myCustomFlag",
    displayName: "My Custom Status",
    description: "RED when MY_REG.MY_BIT is set — indicates [describe condition]",
    type: 'led',
    register: "MY_REG.MY_BIT",
    updateFunc: (instBase) => `((HWREGH(${instBase} + MY_O_REG) & MY_REG_BIT) == MY_REG_BIT)`,
    applicable: (inst) => DEVICES_GEN3.includes(deviceName)
    // Use DEVICES_GEN2 for Gen2 only, or DEVICES_WITH_CDT_SUPPORT for all 15 devices
}
```

### 12.2 Adding a Value Display (Non-LED)

```javascript
{
    name: "myRegisterValue",
    displayName: "My Register Raw Value",
    description: "Displays the raw value of MY_REG field",
    type: 'value',
    register: "MY_REG.MY_FIELD",
    updateFunc: (instBase) => `((HWREGH(${instBase} + MY_O_REG) & MY_REG_FIELD_M) >> MY_REG_FIELD_S)`,
    applicable: (inst) => DEVICES_WITH_CDT_SUPPORT.includes(deviceName)
}
```

### 12.3 Instance Name Mapping

If your SysConfig uses non-default instance names, add explicit mappings to `bitfieldInstanceNames` in the module:

```javascript
const bitfieldInstanceNames = {
    "default": (instName) => { return "Can" + instName + "Regs" },
    "a": (instName) => "CanaRegs",
    "b": (instName) => "CanbRegs",
    "0": (instName) => "CanaRegs",   // numeric aliases
    "1": (instName) => "CanbRegs"
};
```

### 12.4 Device Applicability Constants (Quick Reference)

| Constant | Devices Covered |
|----------|----------------|
| `DEVICES_WITH_CDT_SUPPORT` | All 15 devices (Gen2 + Gen3) |
| `DEVICES_GEN2` | F2802x, F2803x, F2805x, F2806x |
| `DEVICES_GEN3` | All 11 Gen3 devices |
| `DEVICES_WITH_ADCA` | All Gen3 (ADCA on every Gen3 device) |
| `DEVICES_WITH_ADCB` | F28003x, F28004x, F2807x, F2837xD/S, F2838x, F28P55x, F28P65x |
| `DEVICES_WITH_ADCC` | All Gen3 except F2807x |
| `DEVICES_WITH_ADCD` | F2807x, F2837xD/S, F2838x, F28P55x |
| `DEVICES_WITH_ADCE` | F28P55x only |
| `DEVICES_WITH_MCAN` | F280015x, F28003x, F2838x, F28P55x, F28P65x |
| `DEVICES_WITH_AUXPLL` | F2807x, F2837xD/S, F2838x, F28P65x |
| `DEVICES_WITH_MCAN_AUXCLKIN` | F28P55x (MCAN bit clock = external AUXCLKIN pin) |

---

## 13. Frequently Asked Questions

| Question | Answer |
|----------|--------|
| **Does CDT require firmware changes?** | No. CDT reads registers via JTAG. Your application code is untouched. |
| **Does reading registers halt the device?** | No. All reads use non-intrusive JTAG data access. The program continues running. |
| **Can I use CDT on a custom board (not a LaunchPad)?** | Yes. Any XDS probe (XDS110, XDS200, XDS560) with JTAG connectivity will work. |
| **Why does a peripheral not appear in CDT?** | The peripheral must be configured in SysConfig. Add it to `.syscfg`, rebuild, and Refresh Plugins. |
| **Can I use CDT with FreeRTOS or TI-RTOS?** | Yes. CDT operates at hardware register level and does not interact with the OS. |
| **Why is a register missing from Save Registers output?** | CDT skips `RESULT`, `FLAGCLR`, and `FORCE` registers to avoid destructive side effects. |
| **SYSCLK is correct but ADCCLK shows RED. Why?** | Check ADC prescale. ADCCLK must stay within 5–60 MHz (Gen3) or 2–25 MHz (Gen2). |
| **HRPWM shows a RED clock check. What does that mean?** | HRPWMCLK is below the SFO minimum (60 MHz Gen3 / 40 MHz Gen2). SFO MEP calibration will fail. |
| **Can I add my own diagnostics?** | Yes — extend the relevant export module. See [Section 12](#12-customising-cdt). |
| **How do I capture a register dump for a support ticket?** | Click **Save Registers** on the relevant panel to export a full register snapshot. |
| **Can I use CDT while in SCI/SPI export mode instead of debugger?** | Yes. Change the export mode in SysConfig. Note: the CDT GUI panel reads use the debugger regardless; SCI/SPI mode affects only the Export All data transport. |
| **Which C2000Ware version includes CDT?** | CDT has been part of C2000Ware since v4.x. Version 6.x includes the latest Gen2 + Gen3 support. |
| **Why does F28P55x MCAN clock show as unknown/undetermined?** | F28P55x uses AUXCLKIN (an external clock pin) as the MCAN bit clock — CDT cannot read an external pin frequency from registers. Verify AUXCLKIN frequency matches your CAN-FD bit timing requirements. |
| **CPU Timer panel not visible.** | CPUTIMER module not added in SysConfig. Add the CPUTIMER module for the desired instance (0, 1, or 2), rebuild, and Refresh Plugins. |
| **Timer frequency doesn't match firmware.** | Check PRD and prescale values in the CPU Timer panel. Effective frequency = `SYSCLK / ((PRD + 1) × (Prescale + 1))`. Verify SYSCLK in the Clocking panel first. |
| **F28P65x — why is there no ADCD panel?** | F28P65x has only ADCA, ADCB, ADCC (three ADC modules). No ADCD or ADCE is present on this device. |

---

## 14. Additional Resources

| Resource | Link |
|----------|------|
| C2000Ware Download | [ti.com/tool/C2000WARE](https://www.ti.com/tool/C2000WARE) |
| Code Composer Studio | [ti.com/tool/CCSTUDIO](https://www.ti.com/tool/CCSTUDIO) |
| C2000 LaunchPads Overview | [ti.com — C2000 LaunchPads](https://www.ti.com/microcontrollers-mcus/c2000-real-time-control-mcus/overview.html) |
| TI E2E Community — C2000 | [e2e.ti.com/c2000](https://e2e.ti.com/support/microcontrollers/c2000-microcontrollers-group/c2000/f/c2000-microcontrollers-forum) |

---

*Maintained by Zackary Fleenor — hardware accuracy updates applied from CDT source code review.*
