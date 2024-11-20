/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myPWM.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:17:03 by antoda-s          #+#    #+#             */
/*   Updated: 2024/11/19 22:17:13 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringPiSPI.h>
#include <wiringSerial.h>
#include <wiringShift.h>
/* wiringPiSetup(); // Initializes wiringPi using wiringPi's simplified number system. */

void main(void)
{
	wiringPiSetupGpio();
	pinMode(22, INPUT);
	pinMode(23, INPUT);
	pinMode(17, OUTPUT);
	pinMode(18, PWM_OUTPUT);
	digitalWrite(17, HIGH);
	pwmWrite(18, 723);
	delay(2000);
	delay(2000);
}

