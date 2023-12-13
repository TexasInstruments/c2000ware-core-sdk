var longDescriptionObj = {
//*************************************************************************/
// PID
//*************************************************************************/
    "PID":
`# ***Linear PID Controllers***

The basic controller type described here is a linear PID. The PID implementations in the
DCL include several features not commonly found in basic PID designs, and this
complexity is reflected the benchmark figures. Applications which do not require
derivative action, or are more sensitive to cycle efficiency, may be better served by the
simpler PI controller structure described in the next section.

***NOTE***: The DCL contains one implementation of a linear PID controller in double precision
floating point form. This controller may be used with the FPU32 CPU, however support
for the double precision data type currently relies on the run time support libraries which
are not cycle efficient. The structure of the controller is identical to the PID_C1 & PID_C2
controllers described earlier in this chapter. Support functions for PIDF64 do not currently
include the ability to load the controller from transfer function coefficient or ZPK3
descriptions.

PID control is widely used in systems which employ output feedback control. In such
systems, the controlled output is measured and fed back to a summing point where it is
subtracted from the reference input. The difference between the reference and feedback
corresponds to the control loop error and forms the input to the PID controller.

Conceptually, the PID controller output is the parallel sum of three paths which act
respectively on the error, error integral, and error derivative. The relative weight of each
path may be adjusted by the user to optimize transient response, or to emulate the
behavior of a specified transfer function expressed in terms of its poles and zeros.

*Figure: Parallel form PID controller*

![](../../libraries/.meta/control/dcl/images/figures_scaled/Parallel_form_PID_controller-Figure5.png)


The diagram above shows the structure of a continuous time parallel PID controller. The
output of this controller is captured in the following equation:

![](../../libraries/.meta/control/dcl/images/PID_Equation-2.svg)

Conceptually, the controller comprises three separate paths connected in parallel. The
upper path contains an adjustable gain term (Kp). Its effect is to fix the open loop gain of
the control system. Since loop gain is proportional to this term, Kp is known as
proportional gain.
A second path contains an integrator which accumulates error history. A separate gain
term acts on this path. The output of the integral path changes continuously as long as a
non-zero error (e) is present at the controller input. A small but persistent servo error has
the effect of driving the output of the integrator such that the loop error will eventually
disappear. The principal effect of the integral path is therefore to eliminate steady state
error. The effect of the integral gain term is to change the rate at which this happens.
Integral action is especially important in applications such as electronic power supplies,
which must maintain accurate regulation over long periods of time.
The third path contains a differentiator. The output of this path is large whenever the rate
of change of the error is large. The principal effects of the derivative action are to damp
oscillation and reduce transients.
The operation of the PID controller can be visualized in terms of the transient error
following a step change of set-point.

*Figure: PID control action*

![](../../libraries/.meta/control/dcl/images/figures_scaled/PID_control_action-Figure6.png)


The figure above shows the action of the PID controller in terms of the control loop error
at time t1. The proportional term contributes a control effort which is proportional to the
instantaneous loop error. The output of the integral path is the accumulated error history:
the shaded area in the lower plot. The contribution of the derivative path is proportional to
the rate of change of the loop error. Derivative gain fixes the time interval over which a
tangential line to the error curve is projected forward in time.
Tuning the PID controller is a matter of finding the optimum combination of these three
effects. This in turn means finding the best balance of the three gain terms. For more
information on PID control & tuning, see the references in section 6.1.
The PID shown above is known as the “parallel” form because the three controller gains
appear in separate parallel paths. A slightly different PID architecture in which the
proportional gain is moved into the output path (i.e. after the summing point), so that the
proportional path becomes a direct connection between the controller input and the
summing point, is known as the “series” or “ideal” form. In the ideal form, the open loop
gain is directly influenced by the proportional controller gain, and there is less interaction
between the controller gains. However the proportional gain cannot be zero (since the
loop would be opened), and to maintain good control cannot be small. The parallel form
allows the proportional gain to be small, however there is slightly more interaction
between the controller gains, complicating the tuning process. The DCL contains both
ideal and parallel PID functions.

## ***Implementation***

The linear PID controllers in the DCL include the following features:
* Parallel and ideal forms
* Programmable output saturation
* Independent reference weighting on proportional path
* Anti-windup integrator reset
* Programmable low-pass derivative filter
* External saturation input for integrator anti-windup
* Adjustable output saturation

It is important to note that the controller sample period is not accounted for in the selection
of integral gain (Ki). This is relevant when computing the integral gain as opposed to
manual tuning against a transient response, for example. In such situations, users must
multiply the computed integral gain by the sample period before loading Ki (either directly
or through the SPS). The element T in the CSS sub-structure can be used to store the
sample period for this purpose.

All PID type controllers in the library implement integrator anti-windup reset in a similar
way. A clamp is present at the controller output which allows the user to set upper and
lower limits on the control effort. If either limit is exceeded, an internal floating-point
controller variable changes from 1.0 to 0.0. This variable is multiplied by the integrator
input, such that the integrator accumulates zero data only when the output is saturated,
thus preventing the well-known “wind-up” phenomenon.

The PID controllers in the library make provision for anti-windup reset to be triggered from
an external part of the loop. This is useful in situations where a component outside the
controller may be saturated. The floating-point variable lk is expected to be either 1.0 or
0.0 in the normal and saturated conditions respectively. If this feature is not required, the
functions should be called with the lk argument set to 1.0. Note that all the controllers
here require non-zero proportional gain to recover from loop saturation.

The derivative PID path includes a digital low-pass filter to avoid amplification of unwanted
high frequency noise. The filter implemented here is a simple first order lag filter
(with differentiator), converted into discrete form using the Tustin transform. Referring to
Figure 6, the difference equation of the filtered differentiator is

![](../../libraries/.meta/control/dcl/images/PID_Equation-3.svg)

The temporary storage elements d2 & d3 must be preserved from the (k - 1)th interval, so
the following must be computed after the differentiator update.

![](../../libraries/.meta/control/dcl/images/PID_Equation-4.svg)

![](../../libraries/.meta/control/dcl/images/PID_Equation-5.svg)

The derivative filter coefficients are

![](../../libraries/.meta/control/dcl/images/PID_Equation-6.svg)

![](../../libraries/.meta/control/dcl/images/PID_Equation-7.svg)

Both the sample period (T) and filter time constant (tau) must be determined by the user.
The time constant is the reciprocal of the desired filter bandwidth in radians per second.
All linear PID controller functions use a common C structure to hold coefficients and data.
Refer to the header file DCLF32.h for details of the DCL_PID controller structure.
The library PID controller architectures are shown below:

*Figure: DCL_PID C1, C2, & L1 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_PID_C1_C2_L1_architecture-Figure7.png)


*Figure: DCL_PID C3, C4, & L2 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_PID_C3_C4_L2_architecture-Figure8.png)


`,
//*************************************************************************/
// PI
//*************************************************************************/
    "PI":
`# ***Linear PI Controllers***
The continuous time parallel PI control equation is

![](../../libraries/.meta/control/dcl/images/PI_Equation-8.svg)

The linear PI controllers in the DCL differ from the PID in the following respects.
* Removal of derivative path
* Removal of set-point weighting
* No provision for external saturation input

In all other respects, the PI controllers are similar to the PID controllers.

## ***Implementation***

All linear PI controller functions use a common C structure to hold coefficients and data,
defined in the header files DCLF32.h and DCLCLA.h.

The PI controller architectures are shown in the following diagrams.

*Figure: DCL_PI C1, C2, L1, & L3 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_PI_C1_C2_L1_L3_architecture-Figure9.png)


*Figure: DCL_PI C3, C4, L2 & L4 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_PI_C3_C4_L2_L4_architecture-Figure10.png)


*Figure: DCL_PI C5 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_PI_C5_architecture-Figure11.png)


Note that the C5 parallel form PI controller contains enhanced anti-windup reset logic which allows the
integral path to recover from saturation even when the proportional gain is zero.

*Figure: DCL_PI C6, C7, & L5 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_PI_C6_C7_L5_architecture-Figure12.png)

The C6, C7, & L5 controllers combine a series form PI with a Tustin integrator. This configuration
is best suited to applications in which the controller gains are selected on the basis of high
frequency loop gain and zero frequency, because Kp and Ki are effectively un-coupled in the
series form controller. Furthermore the Tustin integrator has fixed 90 degree phase lag at all
frequencies below the Nyquist limit, simplifying design of the compensator.
`,
//*************************************************************************/
// NLPID
//*************************************************************************/
    "NLPID":
`# ***Non-linear PID Controller***
The DCL includes two implementations of a non-linear PID controller, denoted NLPID.
The controllers are broadly similar to the ideal PID_C1 controller, except that there is no
set-point weighting and in one case the derivative path sees the servo error instead of the
feedback. A non-linear gain block appears in series with each of the three paths.

To improve computational efficiency, the non-linear law is separated into two parts: one
part which is common to all paths, and a second part which contains terms specific to
each path. The non-linear part of the high-level controller structure is shown below:

*Figure: DCL_NLPID C1 input architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_NLPID_C1_input_architecture-Figure13.png)


The linear part of the DCL_NLPID_C1 controller is shown below:

*Figure: DCL_NLPID C1 output architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_NLPID_C1_output_architecture-Figure14.png)


*Figure: DCL_NLPID C2 & C3 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_NLPID_C2_C3_architecture-Figure15.png)



The non-linear control law is based on a power function of the modulus of the servo error,
with a linearized region about the zero error point. In the equation below, x represents the
input to the control law, y, the output, and "ALPHA" is a user selectable exponent representing
the degree of non-linearity.

![](../../libraries/.meta/control/dcl/images/NLPID_Equation-9.svg)

The following plot shows the x-y relationship for values of "ALPHA" between 0.2 and 2. Notice
that the curves intersect at x = 0, and x = ±1.

*Figure: Non-linear control law input-output plot*

![](../../libraries/.meta/control/dcl/images/figures_scaled/Non-linear_control_law_input-output_plot-Figure16.svg)


The gain of the control law is the slope of the x-y curve. Observe that with "ALPHA" = 1 the
control is linear with unity gain. With "ALPHA" > 1 the gain is zero when x = 0, and increases as x
increases. In the controller, a value of "ALPHA" in this range produces controller gain which
increases with increasing control error. With 0 < "ALPHA" < 1 the gain at x = 0 is infinite, and falls
as x increases. This range of "ALPHA" setting produces controller gain which decreases with
increasing servo error.

The plots below show the gain vs. control loop error curves for different values of "ALPHA".
Notice particularly the singularity at x = 0 when "ALPHA" < 1.

*Figure: Gain vs error curves for varying alpha*

![](../../libraries/.meta/control/dcl/images/figures_scaled/Gain_vs_error_curves_for_varying_alpha-Figure17.png)


The presence of zero or infinite gain at the zero control error point leads to practical
difficulties. With "ALPHA" > 1 the response becomes sluggish for small errors; with "ALPHA" < 1 it is
common to encounter oscillation or “chattering” near steady-state. These issues can be
overcome by limiting the controller gain in a region close to x = 0. This is done by
modifying the control law to introduce a user selectable region about x = 0 with linear gain
is applied. The non-linear control law becomes

![](../../libraries/.meta/control/dcl/images/NLPID_Equation-10.svg)

When the magnitude of servo error falls below δ the linear gain is applied, otherwise the
gain is determined by the non-linear law. For computational efficiency, we pre-compute
the gain in the linear region ("GAMMA") as follows.

![](../../libraries/.meta/control/dcl/images/NLPID_Equation-11.svg)

A typical plot of the linearized control law is shown below. Observe that when x = δ the
linear and non-linear curves intersect, so the controller makes a smooth transition
between the linear and non-linear regions as the servo error passes through x = ±δ.

*Figure: NLPID linearized region*

![](../../libraries/.meta/control/dcl/images/figures_scaled/NLPID_linearized_region-Figure18.png)


In addition to the P, I, and D gains, the user must select two additional terms in each
control path: "ALPHA" and δ. The library includes a separate function to compute and update "GAMMA"
for each path using the SPS structure. The use must initialize "GAMMA" parameters before calling
the NL controllers.

The NLPID controller has been seen to provide significantly improved control in many
cases, however it must be remembered that increased gain, even if only applied to part of
the control range, can lead to significantly increased output from the controller. In most
cases, this 'control effort' is limited by practical factors such as actuator saturation, PWM
modulation range, and so on. The corollary is that not every application benefits equally
from the use of non-linear control and some may see no benefit at all. In cases where
satisfactory performance cannot be achieved through the use of linear PID control, the
user is advised to start with all "ALPHA" = 1, and experiment by introducing non-linear terms
gradually while monitoring both control performance and the magnitude of the control
effort. In general, P and I paths benefit from increased gain at high servo error ("ALPHA" > 1),
while the D path benefits from reduced gain at high servo error ("ALPHA" < 1), but this is not
universally true. Further information on tuning the nonlinear PID controller can be found
in the Nonlinear PID Controller Tuning Guide in the \docs directory of the DCL.

Further information on this control law can be found in: “From PID to Active Disturbance
Rejection Control”, Jingqing Han, IEEE TRANSACTIONS ON INDUSTRIAL
ELECTRONICS, VOL. 56, NO. 3, MARCH 2009

## ***Implementation***
The NLPID controller uses a C structure to hold coefficients and data, defined in the
header file DCL_NLPID.h. Note that the NLPID functions make use of the pow()
function in the standard C library. For this reason the header file math.h must be
included, which is not supported by the CLA compiler. To allow different DCL functions to
be run on both the CPU and CLA in the same program, the NLPID functions are located in
a separate header file. Refer to the file DCL_NLPID.h for details of the NLPID controller
structure.
`,
//*************************************************************************/
// DF11
//*************************************************************************/
    "DF11":
`# ***Direct Form 1 (First Order) Compensators***
The DCL includes one first order compensator in Direct Form 1. The DF11 compensator
implements a first order, or “simple lag”, type frequency response. The general form of
discrete time first order transfer function is

![](../../libraries/.meta/control/dcl/images/DF11_Equation-12.svg)

Denominator coefficients must be normalized accordingly. The corresponding difference
equation is

![](../../libraries/.meta/control/dcl/images/DF11_Equation-13.svg)

A diagrammatic representation of the DF11 is shown below:

*Figure: DCL_DF11 C1, C2, & L1 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_DF11_C1_C2_L1_architecture-Figure21.png)


## ***Implementation***
All DF11 functions use a common C structure to hold coefficients and data, defined in the
header files DCLF32.h and DCLCLA.h.
`,
//*************************************************************************/
// DF13
//*************************************************************************/
    "DF13":
`# ***Direct Form 1 (Third Order) Compensators***
The Direct Form 1 (DF1) structure is a common type of discrete time control structure
used to implement a control law or dynamical system model specified either as a polezero
set, or as a rational polynomial in z (i.e. a discrete time transfer function). The DCL
includes one third order DF1 compensator, denoted “DF13”.

In general, the Direct Form 1 structure is less numerically robust than the Direct Form 2
(see below), and for this reason users are encouraged to choose the latter type whenever
possible. However, the DCL_DF13 structure is very common in digital power supplies
and for that reason is included in the library. The same function supports a second order
control law after the superfluous coefficients (a3 & b3) have been set to zero.

The general form of third order transfer function is

![](../../libraries/.meta/control/dcl/images/DF13_Equation-14.svg)

Notice that the coefficients have been adjusted to normalize the highest power of z in the
denominator. There is no notational standard for numbering of the controller coefficients;
the notation used here has the advantage that the coefficient suffixes are the same as the
delay line elements and this helps with clarity of the assembly code, however other
notations may be found in the literature. The corresponding difference equation is

![](../../libraries/.meta/control/dcl/images/DF13_Equation-15.svg)

The DF13 controller uses two, three-element delay lines to store previous input and
output data required to compute u(k). A diagrammatic representation is shown below.

*Figure: DCL_DF13 C1, C4, & L1 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_DF13_C1_C4_L1_architecture-Figure22.png)


The DF13 control law consists of seven multiplication operations which yield seven partial
products, and six addition or subtraction operations which combine the partial products to
obtain the compensator output, u(k). When implemented in this way, the control law is
referred to as the “full” DF13 form.

The DF13 control law can be re-structured to reduce control latency by pre-computing six
of the seven partial products which are already known in the previous sample interval.
The control law is then broken into two parts: the “immediate” part and the “partial” part.

The advantage of doing this is to reduce the “sample-to output” delay, or the time between
e(k) being sampled, and a corresponding u(k) becoming available. By partially precomputing
the control law, the computation delay can be reduced to one multiplication
and one addition.

In the kth interval, the immediate part is computed.

![](../../libraries/.meta/control/dcl/images/DF13_Equation-16.svg)

Next, the v(k) partial result is pre-computed for use in the (k+1)th interval.

![](../../libraries/.meta/control/dcl/images/DF13_Equation-17.svg)

Structurally, the pre-computed control law can be drawn as below:

*Figure: DCL_DF13 C2, C3, C5, C6, L2, & L3 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_DF13_C2_C3_C5_C6_L2_L3_architecture-Figure23.png)


The pre-computed structure allows the controller output (u(k)) to be used as soon as it is
computed. The remaining terms in the third order control law do not involve the newest
input e(k) and therefore do not affect u(k). These terms can be computed after u(k) has
been applied to the control loop and the input-output latency of the controller is therefore
reduced.

A further benefit of the pre-computed structure is that it allows the control effort to be
clamped after the immediate part. Computation of the pre-computed part can be made
dependent on the outcome of the clamp such that if u(k) matches or exceeds the clamp
limits there is no point in pre-computing the next partial control variable and the
computation can be avoided. The DCL includes three clamp functions intended for this
purpose.

## ***Implementation***
All DF13 functions use a common C structure to hold coefficients and data, defined in the
header files DCL.h and DCLCLA.h.

The assignment of coefficients and data in the DCL_DF13 structure to those in the
diagram is shown below:

*Figure: DCL_DF13 data & coefficient layout*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_DF13_data_coefficient_layout-Figure24.png)


To implement a full DF13 controller, the user might call:

    uk = DCL_runDF13_C1(&df13, ek);

…where ek and uk are the controller input and output respectively, and df13 is the
controller structure.

To implement a pre-computed DF13 controller, the user might call:

    uk = DCL_runDF13_C2(&df13, ek, vk);
    vk = DCL_runDF13_C3(&df13, ek, uk);

...where vk is an intermediate float variable. This arrangement allows the user to make
use of the output immediately by placing instructions between the two lines above to use
the newest value of uk.

For applications where it is necessary to restrict the output of the compensator, a clamp
function can be used as follows.

    uk = DCL_runDF13_C2(&df13, ek, vk);
    s = DCL_runClamp_C1(&uk, upperLim, lowerLim);
    if (0U == s)
    {
        vk = DCL_runDF13_C3(&df13, ek, uk);
    }

The clamp function limits the controller output to lie between “lowerLim” and “upperLim”
and sets the unsigned integer “s” to 1 is that range is exceeded. The pre-computed part
of the controller will only be executed when the immediate result is in range.
`,
//*************************************************************************/
// DF22
//*************************************************************************/
    "DF22":
`# ***Direct Form 2 (Second Order) Compensators***
The C2000 Digital Controller Library contains a second order implementation of the Direct
Form 2 controller structure, denoted “DCL_DF22”. This structure is sometimes referred to
as a “bi-quad” filter and is commonly used in a cascaded chain to build up digital filters of
high order.

***NOTE***: From version 3.4, the DCL contains support for the DF22 compensator in double precision
floating point. The controller architecture is identical to that described in section 3.8 so
the details need not be repeated here. One full controller and a pair of functions to
support a pre-computed controller are implemented. There are also 'reset' and 'update'
functions, and a double precision clamp function. Other single precision
functions to support coefficient calculation are not implemented at this time.

The transfer function of a second order discrete time compensator is

![](../../libraries/.meta/control/dcl/images/DF22_Equation-18.svg)

The corresponding difference equation is

![](../../libraries/.meta/control/dcl/images/DF22_Equation-19.svg)

A diagrammatic representation of the full Direct Form 2 realization is shown below:

*Figure: DCL_DF22 C1, C4,L1, & L4 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_DF22_C1_C4_L1_L4_architecture-Figure25.png)


As with the DCL_DF13 compensator, sample-to-output delay can be reduced through the
use of pre-computation. The immediate and pre-computed control laws are as follows. In
the kth interval, the immediate part is computed

![](../../libraries/.meta/control/dcl/images/DF22_Equation-20.svg)

Next, the v(k) partial result is pre-computed for use in the (k+1)th interval.

![](../../libraries/.meta/control/dcl/images/DF22_Equation-21.svg)

The pre-computed form of DCL_DF22 is shown in the following diagrams.

*Figure: DCL_DF22 C2, C5, & L2 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_DF22_C2_C5_L2_architecture-Figure26.png)


*Figure: DCL_DF22 C3, C6, & L3 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_DF22_C3_C6_L3_architecture-Figure27.png)


Notice that pre-computation is a little different from the Direct Form 1 case because the
intermediate value exists as one of the internal states and is therefore automatically
stored as “x1” in the DCL_DF22 structure. Therefore it is not necessary to create a
separate variable to store v(k).

## ***Implementation***
All DF22 functions use a common C structure to hold coefficients and data, defined in the
header file DCL.h and DCLCLA.h.
`,
//*************************************************************************/
// DF23
//*************************************************************************/
    "DF23":
`# ***Direct Form 2 (Third Order) Compensators***
The third order Direct Form 2 compensator (DF23) is similar in all respects to the DF22
compensator. Separate full and pre-computed forms are supplied in C and assembly for
computation on the FPU32, and in assembly for computation on the CLA.
The control law is the same as the DF13 compensator.

![](../../libraries/.meta/control/dcl/images/DF23_Equation-23.svg)

A diagrammatic representation of the full third order Direct Form 2 compensator is shown
below:

*Figure: DCL_DF23 C1, C4, & L1 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_DF23_C1_C4_L1_architecture-Figure28.png)


Sample-to-output delay can be reduced through the use of pre-computation, in a similar
way to the DF22 compensator. In the kth interval, the immediate part is computed.

![](../../libraries/.meta/control/dcl/images/DF23_Equation-24.svg)

Next, the v(k) partial result is pre-computed for use in the (k+1)th interval.

![](../../libraries/.meta/control/dcl/images/DF23_Equation-25.svg)

The pre-computed form of DF23 is shown in the following diagrams:

*Figure: DCL_DF23 C2, C5, & L2 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_DF23_C2_C5_L2_architecture-Figure29.png)


*Figure: DCL_DF23 C3, C6, & L3 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_DF23_C3_C6_L3_architecture-Figure30.png)


## ***Implementation***
All DF23 functions use a common C structure to hold coefficients and data, defined in the header
file DCL.h. and DCLCLA.h.
`,
//*************************************************************************/
// PID32
//*************************************************************************/
    "PID32":
`# ***Fixed-Point PID Controllers***
The DCL contains one implementation of a parallel form fixed-point PID controller. The
structure is similar to the floating-point C1 controller.

The linear PID controller in the DCL32 includes the following features.
* Parallel form
* Programmable output saturation
* Anti-windup integrator reset
* Programmable low-pass derivative filter
* Feedback input to derivative path

Both PID and PI type controllers in the DCl32 library implement integrator anti-windup
reset in a similar way. A clamp is present at the controller output which allows the user to
set upper and lower limits on the control effort. If either limit is exceeded, an internal
floating-point controller variable changes from logical 1 to logical 0. This variable is
converted into Q24 format and multiplied by the integrator input, such that the integrator
accumulates successive zero data when the output is saturated, avoiding the “wind-up”
phenomenon.

The following equations describe the implementation of the PID32 controller. Note that
the storage of static variables {i14 i10 d2 d3} is not shown.

The servo error equation is

![](../../libraries/.meta/control/dcl/images/PID32_Equation-26.svg)

The proportional path equation is

![](../../libraries/.meta/control/dcl/images/PID32_Equation-27.svg)

The integral path equations are

![](../../libraries/.meta/control/dcl/images/PID32_Equation-28.svg)

![](../../libraries/.meta/control/dcl/images/PID32_Equation-29.svg)

![](../../libraries/.meta/control/dcl/images/PID32_Equation-30.svg)

The derivative path equations are

![](../../libraries/.meta/control/dcl/images/PID32_Equation-31.svg)

![](../../libraries/.meta/control/dcl/images/PID32_Equation-32.svg)

![](../../libraries/.meta/control/dcl/images/PID32_Equation-33.svg)

![](../../libraries/.meta/control/dcl/images/PID32_Equation-34.svg)

Note that the derivative coefficient c1 must be divided by two on initialization. This
element is typically much larger than c2 so we enter half its value in the code and multiply
twice. This allows greater numerical range for a given Q-format.

The output path equations are

![](../../libraries/.meta/control/dcl/images/PID32_Equation-35.svg)

![](../../libraries/.meta/control/dcl/images/PID32_Equation-36.svg)

![](../../libraries/.meta/control/dcl/images/PID32_Equation-37.svg)

![](../../libraries/.meta/control/dcl/images/PID32_Equation-38.svg)

![](../../libraries/.meta/control/dcl/images/PID32_Equation-39.svg)

The DCL_PID32 implementation is shown below:

*Figure: DCL_PID32 A1 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_PID32_A1_architecture-Figure31.png)


The linear PID_A1 controller uses a C structure to hold coefficients and data, defined in
the header file DCLC28.h. The order of these structure elements must not be changed
by the user.
`,
//*************************************************************************/
// PI32
//*************************************************************************/
    "PI32":
`# ***Fixed-Point PI Controllers***
The DCL contains one implementation of a fixed-point series form PI controller. The PI is
similar in operation to the PID controller, with the removal of the derivative path.

## ***Implementation***

The following equations describe the implementation of the PI32 controller.

![](../../libraries/.meta/control/dcl/images/PI32_Equation-40.svg)

![](../../libraries/.meta/control/dcl/images/PI32_Equation-41.svg)

![](../../libraries/.meta/control/dcl/images/PI32_Equation-42.svg)

![](../../libraries/.meta/control/dcl/images/PI32_Equation-43.svg)

![](../../libraries/.meta/control/dcl/images/PI32_Equation-44.svg)

![](../../libraries/.meta/control/dcl/images/PI32_Equation-45.svg)

![](../../libraries/.meta/control/dcl/images/PI32_Equation-46.svg)

![](../../libraries/.meta/control/dcl/images/PI32_Equation-47.svg)

![](../../libraries/.meta/control/dcl/images/PI32_Equation-48.svg)

The ideal form PI implementation is shown below:

*Figure: DCL_PI A1 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_PI_A1_architecture-Figure32.png)


The linear PI controller uses a C structure to hold coefficients and data, defined in the
header file DCLC28.h. The order of these structure elements must not be changed by
the user.
`,
//*************************************************************************/
// PI2
//*************************************************************************/
    "PI2":
`# ***Double Integrator PI Controller***
The DCL contains one implementation of a linear PI controller having two series
integrators. This type of controller is similar to the parallel PI controller
except that the anti-windup reset logic is more complicated.

In this controller, allowance has been made for the Kp element to be zero. This scenario
presents a problem if the controller enters saturation because without the proportional
path there is no way to recover. The PI2 resolves this by releasing the anti-windup lock
when the integrator input reverses sign. The logic has to be implemented twice, since
there are two cascaded integrators. Similar anti-windup reset logic is present in the
PI_C5 controller.

## ***Implementation***
The double integrator PI2 controller uses a C structure to hold coefficients and data,
defined in the header file DCLF32.h.

The PI2 implementation is shown below:

*Figure: DCL_PI2 C1 architecture*

![](../../libraries/.meta/control/dcl/images/figures_scaled/DCL_PI2_C1_architecture-Figure20.png)
`,
}

function get_longDescriptionObj()
{
    return longDescriptionObj;
}

exports = {
    get_longDescriptionObj:get_longDescriptionObj,
}