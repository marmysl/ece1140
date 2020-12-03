#ifndef SPEEDREGULATOR_H
#define SPEEDREGULATOR_H

#include <cstdint>
#include "../TrainModel/Train.h"
#include <QObject>
#include <QTimer>
#include <QDateTime>
#include "../CTCOffice/ctcoffice/CTCMode.h"
#include "BeaconDecoder.h"


class SpeedRegulator
{
private:
        Train *trainModel;
        CTCMode *mode;
        BeaconDecoder* beacon;
        double setpointSpeed;
        double Vcmd;
        double powerCmd;
        double Kp;
        double Ki;
        double uk;
        double uk_1;
        double ek;
        double ek_1;
        double T;
        double maxPower;
        double commandedSpeed;
        int authority;
        QDateTime prevTime;
        QDateTime currTime;
        int failureCode;

    public:

        /*!
            Constructor that initializes a SpeedRegulator object
            @pre: none
            @post: a SpeedRegulator object is created with initialized member variabeles
            @param: Train object pointer that is used to communicate with the Train Model
            @param: CTCMode object pointer used to operate in automatic vs. manual mode
            @param: BeaconDecoder object pointer used to extract informations from beacons
            @throw: none
            @return: none
        */
        SpeedRegulator(Train*, CTCMode*, BeaconDecoder*);

        /*!
            Method that chooses the proper Vcmd to be used in the power command calculation
            Vcmd will be the commanded speed in automatic mode, or the lower of setpoint speed or
            commanded speed in manual mode.
            @pre: track circuit data has been sent from the train and decoded by the train controller
            @post: Vcmd has been updated according to the setpoint speed, commanded speed, and mode
            @param: none
            @throw: none
            @return: none
        */
        void chooseVcmd();

        /*!
            Method that increments/decrements the setpoint speed by the number provided in the parameter
            Converts the increment to km/hr before adding/subtracting it with setpointSpeed
            Ensures that the setpoint speed does not go below 0 km/hr or exceed 70 km/hr
            @pre: none
            @post: the setpoint speed is updated and Vcmd is updated accordingly
            @param: double inc (in mi/hr): if inc is positive, the setpoint speed increases to the value
                                           converted to km/hr
                                           if inc is negative, the setpoint speed decreases to the value
                                           converted to km/hr
            @throw: none
            @return: none
        */
        void incSetpointSpeed(double inc);


        /*!
            Method that calculates a power value in Watts according to the PID loop equation
            @pre: none
            @post: a power value is returned to be compared with others in the calcPowerCmd() method
            @param: none
            @throw: none
            @return: none
        */
        double powerFormula();

        /*!
            Method that compares three power calculations redundantly. If at least two of the three are
            the same within a 3W margin of error, the power command is set to their average. Otherwise,
            the emergency brake is pulled because the power calculations are incorrect.
            @pre: none
            @post: a valid (between -120 kW and 120W) power command is sent to the Train in Watts
            @param: none
            @throw: none
            @return: none
        */
        void calcPowerCmd();

        /*!
            Method that handles setting the power command to 0. It sets pcwerCmd to 0, sets the power in
            the train model to 0, sets PID loop variables like ek_1 and uk_1 to 0, and decreases the
            setpoint speed to 0
            @pre: emergency or service brakes have been pulled, commanded speed is 0, or authority is 0
            @post: powerCmd = 0, setpointSpeed = 0, Train's power is 0, ek_1 = 0, and uk_1 = 0
            @param: none
            @throw: none
            @return: none
        */
        void powerCmdZero();

        /*!
            Mutator function that sets the values of Kp and Ki according to the train engineer input in
            the arduino and converts them from kW to W
            @pre: the Arduino is in setup mode and is not reading any values from the program
            @post: Kp and Ki are set, Serial Port communication commences
            @param: double propGain : represents Kp, which is given in W/(m/s)
            @param: double intGain : represents Ki, which is given in W/m
            @throw: none
            @return: none
        */
        void setKpAndKi(double propGain, double intGain);

        /*!
            Function that activates the serivce brake, sets the power to 0, and resets the
            setpoint speed
            @pre: none
            @post: the service brake is activated, power is 0, and the setpoint speed is 0
            @param: none
            @throw: none
            @return: none
        */
        void pullServiceBrake();

        /*!
            Function that activates the emergency brake, sets the power to 0, and resets the
            setpoint speed
            @pre: none
            @post: the emergency brake is activated, power is 0, and the setpoint speed is 0
            @param: none
            @throw: none
            @return: none
        */
        void pullEmergencyBrake();

        /*!
            Method that sets the failure code for the system whenever a failure is detected
            0 = no failure
            1 = track signal pickup failure
            2 = engine failure
            3 = brake failure
            @pre: a failure is detected within the system
            @post: the failure of the system has been updated; if the failure code is not 0, the emergency
                   brake is pulled
            @param: an integer (0-3) that represents the failure code as encoded above
            @throw: none
            @return: none
        */
        void setFailureCode(int fc);

        /*!
            Method that decodes the track circuit and moniters for track circuit failure
            @pre: none
            @post: the current track circuit values are computed and sent to the commandedSpeed and authority
                   member variables; if the track circuit is recieved as 0xfffffffffffffff, then the failure code
                   is set to 1
            @param: none
            @throw: none
            @return: none
        */
        void decodeTrackCircuit();

        /*!
            Accessor method that returns the value in setpointSpeed
            @pre: none
            @post: the current setpoint speed is returned
            @param: none
            @throw: none
            @return: a double holding the setpointSpeed
        */
        double getSetpointSpeed();

        /*!
            Accessor method that recalculates the power command and returns powerCmd
            @pre: none
            @post: the current power being sent to the train is calculated and returned
            @param: none
            @throw: none
            @return: a double holding the powerCmd
        */
        double getPowerCmd();

        /*!
            Accessor method that recalculates and returns the current velocity command used in power calculations
            @pre: none
            @post: the result of getVcmd() method is returned
            @param: none
            @throw: none
            @return: a double holding Vcmd
        */
        double getVcmd();

        /*!
            Accessor method that returns the proportional gain value
            @pre: none
            @post: the proportaional gain is returned
            @param: none
            @throw: none
            @return: a double holding Kp
        */
        double getKp();

        /*!
            Method that returns the integral gain value
            @pre: none
            @post: the integral gain is returned
            @param: none
            @throw: none
            @return: a double holding Ki
        */
        double getKi();

        /*!
            Accessor method that returns the failure code
            @pre: none
            @post: the current failureCode is returned
            @param: none
            @throw: none
            @return: an integer with value 0, 1, 2, or 3 is returned
        */
        int getFailureCode();

        /*!
            Accessor method that decodes the track circuit and returns the commanded Speed
            @pre: none
            @post: the current commanded Speed is returned
            @param: none
            @throw: none
            @return: an double containing the decoded commanded speed in km/hr
        */
        double getCommandedSpeed();

        /*!
            Accessor method that decodes the track circuit and returns the authority
            @pre: none
            @post: the authority is returned
            @param: none
            @throw: none
            @return: an int containing the authority in number of blocks
        */
        int getAuthority();

};
#endif
