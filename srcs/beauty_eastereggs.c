/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beauty_eastereggs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 00:02:30 by iwillens          #+#    #+#             */
/*   Updated: 2020/05/14 00:14:49 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	egg_prt1(void)
{
	ft_putstr_color("#0                                   #H #0 \n#0   ");
	ft_putstr_color("              #H  #0               #H  #0 \n#0    ");
	ft_putstr_color("             #H #I #H #0             #H #I #H #0 ");
	ft_putstr_color("\n#0                 #H #I  #H  #0          #H #I  ");
	ft_putstr_color("#H #0 \n#0                 #H #I    #H #0        ");
	ft_putstr_color("#H #I   #H #0  \n#0                 #H #I     #H #0");
	ft_putstr_color("      #H #I     #H #0              #H   #0 \n#0   ");
	ft_putstr_color("              #H #I      #H  #0   #H #I      #H #0");
	ft_putstr_color("          #H   #I  #H #0 \n#0                #H #I");
	ft_putstr_color("         #H #0 #H #I       #H #0      #H    #I    ");
	ft_putstr_color("#H #0 \n#0    #H       #0     #H #I          #H #I");
	ft_putstr_color("         #H #0  #H    #I       #H #0 \n#0    #H #I");
	ft_putstr_color("      #H    #0 #H #I                    #H   #I   ");
	ft_putstr_color("       #H #0 \n#0     #H #I         #H  #I        ");
	ft_putstr_color("                        #H #0 \n#0      #H #I     ");
	ft_putstr_color("       #G                  #I           #H #0 \n#0");
	ft_putstr_color("       #H  #I        #G  #J                  #G  ");
	ft_putstr_color("#I         #H #0 \n#0       #H  #I      #G #J      ");
	ft_putstr_color("                #G #I       #H #0 \n#0          #H");
	ft_putstr_color(" #I    #G #J                        #G #I     #H ");
	ft_putstr_color("#0 \n#0           #I   #G #J #I     #J             ");
	ft_putstr_color("#I    #J #G #I    #H #0 \n#H            #I  #G #J ");
	ft_putstr_color(" #G     #I   #J      #I    #G    #J  #G #I   #H   ");
	ft_putstr_color("          #0 \n#H #I             #G #J     #G     ");
}

void	egg_prt2(void)
{
	ft_putstr_color("#I      #G     #J     #G #I              #H #0 \n");
	ft_putstr_color("#0 #H  #I           #G #J          #G      #J      ");
	ft_putstr_color("    #G #I            #H  #0 \n#0   #H  #I         ");
	ft_putstr_color("#G #J     #G     #J      #G     #J     #G #I      ");
	ft_putstr_color("    #H  #0 \n#0     #H #I        #G #J    #G #J   ");
	ft_putstr_color("  #G #J    #G #J     #G #J    #G #I        #H  #0 ");
	ft_putstr_color("\n#0      #H  #I      #G #J   #G         #J  #G   ");
	ft_putstr_color("      #J   #G #I       #H #0 \n#0        #H #I    ");
	ft_putstr_color(" #G #J   #G #H   #G #H   #G #J  #G #H   #G #H   #G");
	ft_putstr_color(" #J   #G #I     #H  #0 \n#0      #H  #I    #G   #J");
	ft_putstr_color("    #G #H     #G #J    #G #H     #G #J    #G   #I ");
	ft_putstr_color(" #H #0 \n#0     #H #I     #G #J  #G #J     #G     ");
	ft_putstr_color("#J      #G     #J     #G #J  #G #I  #H #0 \n#0    ");
	ft_putstr_color("#H #I      #G #J  #G #J  #G #J        #G #J  #G #J");
	ft_putstr_color("        #G #J  #G #J  #G #I   #H  #0 \n#0   #H    ");
	ft_putstr_color("  #I  #G #J  #G #J   #G     #J   #G #J  #G #J   #G");
	ft_putstr_color("     #J   #G #J  #G #I     #H #0 \n#0        #H #I");
	ft_putstr_color("   #G #J #G #J           #G #J  #G #J           #G");
	ft_putstr_color(" #J #G #I  #H      #0 \n#0       #H #I     #G  #J ");
	ft_putstr_color("           #G  #J            #G  #I    #H #0 \n#0 ");
	ft_putstr_color("     #H     #I   #G #J    #G #J                 #G");
	ft_putstr_color(" #J   #G #I      #H #0 \n#0         #H #I    #G #J");
	ft_putstr_color("   #G #J  #G              #J   #G #J  #G #I    #H ");
	ft_putstr_color("   #0 \n#0        #H #I    #H #G #J   #G #J       ");
	ft_putstr_color("#G #K     #G #J     #G #J  #G #H #I   #H #0  \n#0 ");
}

void	print_easteregg(void)
{
	egg_prt1();
	egg_prt2();
	ft_putstr_color("      #H #I   #H #0  #G #J   #G  #J      #G #K   ");
	ft_putstr_color("#G #J    #G  #J  #G #0  #H #I  #H #0 \n#0        #H");
	ft_putstr_color(" #I #H  #0   #G #J           #G  #K  #G #J        ");
	ft_putstr_color("#0   #H  #I #H #0 \n#0        #H  #0      #G #J   ");
	ft_putstr_color("         #G  #J        #G #0      #H  #0 \n#0     ");
	ft_putstr_color("            #G #J                    #G #0 \n#0   ");
	ft_putstr_color("               #G  #J                #G  #0  \n#0 ");
	ft_putstr_color("                   #G                #0 \n");
}
