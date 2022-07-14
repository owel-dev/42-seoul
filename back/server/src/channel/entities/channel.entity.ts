import { Column, Entity, PrimaryGeneratedColumn } from "typeorm"

@Entity('channel')
export class ChannelEntity
{
    @PrimaryGeneratedColumn()
    channelId : number;

    @Column()
    player1: string;
    
    @Column()
    player2: string;

    @Column()
    admin: string;

    @Column()
    curNumUser : number;

    @Column()
    maxNumUser : number;
    
    @Column()
    password : string;

    @Column()
    mode: number;

    @Column()
    type: number;

    // @Column()
    // muteList: number;


    
}
