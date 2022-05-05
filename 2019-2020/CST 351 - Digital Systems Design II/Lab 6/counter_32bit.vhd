--`timescale 1ns / 1ps
-----------------------------------------------------------------------------------
-- Company: Oregon Institute of Technology
-- Engineer: Zak Rowland
-- 
-- Create Date: 10:32:00 05/19/2020 
-- Design Name: 
-- Module Name: counter_32bit
-- Project Name: Lab6
-- Target Devices: Cyclone V - DE1-SoC
-- Tool versions: Quartus Lite 19.1
-- Description: 32-bit counter in VHDL
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

entity counter_32bit is
	port
	(
		clk : in std_logic; -- Clock input
		clear : in std_logic; -- '0' to run as usual, '1' to clear counter
		load : in std_logic; -- '0' to run as usual, '1' to load 'input_val' into counter
		up_down : in std_logic; -- '0' to count down, '1' to count up
		input_val : in integer range 0 to ((2**31)-1); -- 32-bit input value to load into counter
		counter_out : out integer range 0 to ((2**31)-1) -- 32-bit output value of counter
	);
end entity;

architecture rtl of counter_32bit is begin

	process(clk)
		variable count : integer range 0 to ((2**31)-1);
		variable dir : integer;
	begin
		if up_down = '1' then dir := 1;
		else dir := -1;
		end if;
		
		if(clk'event and clk = '1') then -- Rising edge
			if clear = '1' then -- If clear, clear counter
				count := 0;
			else
				if load = '1' then count := input_val; -- If load, store input val
				else count := dir; -- Increment (or decrement) counter
				end if;
			end if;
		end if;
		counter_out <= count; -- Assign output
	end process;

end rtl;