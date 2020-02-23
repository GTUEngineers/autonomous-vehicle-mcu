# Autonomous-Vehicle

Teknofest Robotaksi Otonom Araç Yarışması - Gebze Technical University Team


We've used STM32F407G Discovery as microcontroller. You can easily import the project in STM32IDE. 



# Messages of UART Communication 

    0000 0000 0000 0000 0000 0000 -> Packet(24 bit) 

Fırst 8 bits are header,  
Last 16 bits are data

### Start Stop REQ
#### Start Stop Header

    0000 0000 

#### Start Stop Data
    0000 0000 0000 0000 STOP
    
    0000 0000 0000 0001 START 

### Steering REQ
#### Steering Header

    0000 0001 

#### Steering Data

    0000 XXXX XXXX XXXX left steering val
    
    0001 XXXX XXXX XXXX right steering val

### Throttle REQ
#### Throttle Header

    0000 0010 

### Throttle Data

    XXXX XXXX XXXX XXXX throttle value

### Brake REQ
#### Brake Header

    0000 0011

### Brake Data

    0000 0000 0000 0000 Release
    
    0000 0000 0000 0001 Lock

### Generic REP 
#### Generic Rep Header

    0000 0100

#### Generic Rep Data

    0000 0000 0000 0000 Error
    
    0000 0000 0000 0001 Ok


### State REQ 
#### State REQ Header

    0000 0101

####  State  REQ Data

    0000 0000 0000 0000 (Don't care)

### State REP 
#### State REP Header

    0000 0110

####  State REP Data

    0000 0000 0000 0000 STOP
    
    0000 0000 0000 0001 Running
    
    0000 0000 0000 0010 Error