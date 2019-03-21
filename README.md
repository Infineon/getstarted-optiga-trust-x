# Infineon's OPTIGA&trade; Trust X Get Started Guide

## Description

This repository contains one of Application Notes for [OPTIGA™ Trust X](https://www.infineon.com/cms/en/product/security-smart-card-solutions/optiga-embedded-security-solutions/optiga-trust/optiga-trust-x-sls-32aia/) security chip.

* **You can find step-by-step get started guide on the [Wiki page](https://github.com/Infineon/getstarted-optiga-trust-x/wiki) of the project**
* You can find more information about the security chip in the core [repository](https://github.com/Infineon/optiga-trust-x)
* You can find other Application Notes in the respective [repository](https://github.com/Infineon/appnotes-optiga-trust-x)

## Summary
In this guide you may find the following steps:
* How to import this project into the DAVE™ IDE
* How to build the software and flash the development board (described below)
* How to debug and run examples for all Tool Box functions, nameley: 
    * sign message (ECDSA)
    * verifiy the ECDSA signature
    * calculate SHA-256 hash
    * generate public private key pair (NIST P256/P384)
    * calculate shared secret (ECDH)
    * derive a key (TLS PRF with SHA-256) 

## Hardware and Software
<p align="center">
  <img src="https://www.infineon.com/export/sites/default/_images/product/evaluation-boards/OPTIGA-trust-x-eval-kit.jpg_123076721.jpg">
</p>

* This get started guide uses the [OPTIGA™ Trust X evaluation and demonstration kit](https://www.infineon.com/cms/en/product/evaluation-boards/optiga-trust-x-eval-kit/)
* This get started guide uses DAVE™ IDE as a reference software development platform
* You need a Windows OS in order to follow this guide

## Contributing
Please read [CONTRIBUTING.md](https://github.com/Infineon/arduino-optiga-trust-x/blob/master/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
