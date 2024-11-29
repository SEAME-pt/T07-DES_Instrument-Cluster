---
# Configuration of the communication system between all components of the vehicle in SEA:ME context, to control the Racer "Waveshare" 
parent: Decisions
nav_order: 003
title: Communications System Architecture Decision Record

## status: proposed
## date: 2024-11-29
## decision-makers: 
   - Nuno Taboada
   - Heitor Maciel
   - Ivo Marques
   - Antonio Ferreira

## consulted: 
  - Felipe Prezado (fp@seame.pt)
  - Pedro Batista (pb@seame.pt)
  - Paulo Silva (ps@seame.pt)
## informed: 
  - Felipe Prezado (fp@seame.pt)
  - Pedro Batista (pb@seame.pt)
  - Paulo Silva (ps@seame.pt)
---
<!-- we need to disable MD025, because we use the different heading "ADR Template" in the homepage (see above) than it is foreseen in the template -->
<!-- markdownlint-disable-next-line MD025 -->
# Which Communications Protocls

## Context and Problem Statement

The ADR 001 (#23 ) considered a multiple platform hardware architecture. This ADR together with the Course Book subject requires multiple communications protocols.
Some protocols are bare naked requirement as for the CAM and for the TFTLCD, others are required by the subject and lastly required by the above mentioned ADR 001.

<!-- This is an optional element. Feel free to remove. -->
## Decision Drivers

* the features and settings challenges of multiple hardware platforms
* integration of different types of control hardware, from CPU, GPU and MicroController universe of hardware sensors and displays
* implementation of performant solutions when implementing in AI and ML
<!-- numbers of drivers can vary -->

## Considered Options
### Comparison Table

| Protocol | Bandwidth      | Distance       | Latency | Robustness | Security | Cost  | Use Cases                                   |
|----------|----------------|----------------|---------|------------|----------|-------|--------------------------------------------|
| TCP/IP   | High           | Long (Global)  | High    | Moderate   | High     | High  | Cloud integration, diagnostics             |
| CAN      | Low (1 Mbps)   | Medium (~40m)  | Low     | High       | Low      | Low   | Intra-vehicle communication, safety        |
| I²C      | Low (400 kbps) | Short (~1m)    | Low     | Moderate   | Low      | Low   | Sensors, low-speed peripherals             |
| SPI      | High (10+ Mbps)| Short (~10m)   | Low     | Moderate   | Low      | Low   | High-speed sensors, displays, ADCs         |

---

## Decision Outcome
1. **Intra-Vehicle ECU Communication**: Use **CAN** for its real-time capabilities and reliability.
2. **ECU-to-Peripheral Communication**: Use **I²C** for low-speed peripherals and **SPI** for high-speed peripherals.
3. **Vehicle-to-Cloud/External Systems**: Use **TCP/IP** for diagnostics, telemetry, and software updates.

---

<!-- numbers of drivers can vary -->


<!-- This is an optional element. Feel free to remove. -->
#### Consequences

##### Benefits
* The learning journey most likely will fill the knowledge goals
* The requirements will be fully  implemented

##### Drawbacks
 * complexity and fail pruner
 * tighter schedule

### Confirmation

At the end of the first product, "DES_Instrument _Cluster", the decision shall be confirmed as  VALID or INVALID
with report of of the pros and cons faced during the first product development.

<!-- This is an optional element. Feel free to remove. -->


