import { User } from "src/users/entities/user.entity";
import { Column, Entity, PrimaryColumn } from "typeorm";

@Entity('stats')
export class Stat {

	@PrimaryColumn()
	intra_id: string;

	@Column()
	win: number;

	@Column()
	lose: number;

	@Column({type: 'real'})
	winrate: number;
}
