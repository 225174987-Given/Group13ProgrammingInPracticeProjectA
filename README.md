# Municipal Financial Management System (MFMS) - Foundation System

##  Project Information
* **Course:** PAP521S – Programming in Practice
* **Project Stage:** Project A (Foundation System)
* **Programming Language:** ANSI C (C99 Standard)
* **Development Environment:** Visual Studio Code + GCC Compiler
* **Group Number:** Group 13

##  Group Members & Module Allocation
* **Student 1 (225174987-given):** Employee Management Module
* **Student 2 (224097369-quentos):** Budget Management Module
* **Student 3 (222132892-hukura):** Supplier Management Module
* **Student 4 (225164922-mahoshi):** Asset Register Module
* **Student 5 (225083108-josephat):** Reports Summary Module
* **Student 6 (lennonkandambo-netizen):** Structural Functions & System Validation
* **Student 7 (226009742-mbambi):** Integration Testing, Documentation & Git Coordination

##  Compilation and Execution Instructions
To compile all modules together into a unified system binary executable using GCC, run this command in your terminal window:
```bash
gcc main.c employees.c budget.c suppliers.c assets.c reports.c -o MFMS
```

To execute and run the system interface application, execute this command:
```bash
./MFMS
```

##  System Core Features
* **Employee Registry:** Add personnel files, view staff arrays, and calculate dynamic gross salary packages with structural allowances.
* **Budget Tracking:** Record maximum department allowances, log spending outlays, balance remaining equations, and generate warning flags for over-budget departments.
* **Supplier Indexing:** Maintain a vendor database containing IDs, company names, emails, phones, and town locations.
* **Asset Ledger:** Track municipal infrastructure properties, structural valuations, and condition metrics.
* **Telemetry Reporting:** Compile system-wide statistics including high/low salary tiers and capital expenditure summaries.

##Testing and Input Validation Framework[]
The application implements strict boundary validation rules across all modules:
1. **Menu Interface Check:** Alphanumeric inputs or choice selections out of bounds do not crash the menu lifecycle.
2. **Financial Data Guard:** Data structural layers cleanly halt execution and reject any negative salary or budget figures.
3. **String Safety:** Uses standard string processing (`strcmp`, `strlen`) to ensure query matching and buffer protection across indexing components.

Individual Contribution Record — Student 6
• Assigned Role: System Functions, Integration, and Data Validation Lead.
• Modules/Functions Developed:
◦ Designed and built the global system architecture entry hub (01_main.c) handling nested menu control routing loops for all modules.
◦ Engineered input sanitation methods by standardizing input buffer flushes (while(getchar()!='\n')) across structural switch conditions to prevent application crash loops.
◦ Implemented the shared system color variables (02_common.h) to enforce unified CLI aesthetics across the program framework.
• Integration Strategies Implemented:
◦ Successfully debugged cross-module link errors by fixing structural incompatibilities between the Employee Management parallel arrays and the Reports generation logic (12_Report.c).
◦ Resolved compile-time scope exceptions through targeted explicit forward function prototyping across the multi-file build system.
