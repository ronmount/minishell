/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:16:42 by                   #+#    #+#             */
/*   Updated: 2021/10/21 20:00:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int argc, char **argv, char **env)
{
    (void) argc;
    (void) argv;
    (void) env;


    t_data *data = malloc(sizeof(t_data));
    while (1)
    {
        data->query = readline("minishell> ");
        parse(data);
    }
}
