// Fig. 6.25: maximum.h
// Definition of function template maximum.
template < class T >  // or template< typename T >
T maximum( T value1, T value2, T value3 )                  
{                                                          
	T maximumValue = value1; // assume value1 is maximum

	// determine whether value2 is greater than maximumValue											
	if ( value2 > maximumValue )                            
		maximumValue = value2;                               

	// determine whether value3 is greater than maximumValue
	if ( value3 > maximumValue )                            
		maximumValue = value3;                               
	return maximumValue;                                    
} // end function template maximum

unsigned long long recursiveFactorial(unsigned long value)
{
	if (value <= 1)
	{
		value = 1;
	}
	else 
	{
		value = value * recursiveFactorial(value -1);
	}
	return value;
}
template < typename T >
T values( T value, T min, T max )
{
	T finalValue = min;

	if (value == min)
	{
		std::cout << "value " << value << " = min value " << min << std::endl;
	}
	if (value == max)
	{
		std::cout << "value " << value << " = max value " << max << std::endl;
	}
	if ( (value < min) && (value > max) )
	{
		std::cout << "value " << value << " outside of min value " << min 
			<< " and max value " << max << " set to min value" << std::endl;
	}
	if ( (value >= min) && (value <= max) )
	{
		finalValue = value;
		std::cout << "Value has been set to " << finalValue << std::endl;
	}
		
	std::cout << "Value + Min = " << value + min << std::endl;
	std::cout << "Value + Max = " << value + max << std::endl;
	std::cout << "Value - Min = " << value - min << std::endl;
	std::cout << "Value - Max = " << value - max << std::endl;
	std::cout << "Value * Min = " << value * min << std::endl;
	std::cout << "Value * Max = " << value * max << std::endl;
	std::cout << "Value / Min = " << value / min << std::endl;
	std::cout << "Value / Max = " << value / max << std::endl;

	return finalValue;
}

