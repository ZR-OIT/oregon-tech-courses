--`timescale 1ns / 1ps
-----------------------------------------------------------------------------------
-- Company: Oregon Institute of Technology
-- Engineer: Zak Rowland
-- 
-- Create Date: 09:32:00 05/19/2020 
-- Design Name: 
-- Module Name: lab6_top
-- Project Name: Lab6
-- Target Devices: Cyclone V - DE1-SoC
-- Tool versions: Quartus Lite 19.1
-- Description: Counters and UART in VHDL
--
-- Dependencies:
--
-- Revisions: 
-- - Revision 0.01: File Created
-- Additional Comments: 
--
-----------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

entity lab6_top is
	port
	(
		CLOCK_50 : in std_logic; -- 50MHz clock input
		SW : in std_logic_vector (9 downto 0); -- 10 input switches
		KEY : in std_logic_vector (3 downto 0); -- 4 input buttons
		LEDR : out std_logic_vector (9 downto 0) -- 10 output LEDs
	);
end lab6_top;

architecture rtl of lab6_top is

	component counter_32bit
		port
		(
			clk, clear, load, up_down : in std_logic;
			input_val : in integer range 0 to ((2**31)-1);
			counter_out : out integer range 0 to ((2**31)-1)
		);
	end component;
	
	signal load_value : unsigned(integer range 0 to ((2**31)-1);
	signal counter_value : integer range 0 to ((2**31)-1);
	
	begin
	
	counter_instance : counter_32bit port map (clk => CLOCK_50, clear => SW(0), load => SW(1), up_down => SW(2), input_val => load_value, counter_out => counter_value);

end rtl;