import { User } from "src/users/entities/user.entity";
import { Column, Entity, ManyToOne, PrimaryColumnCannotBeNullableError, PrimaryGeneratedColumn } from "typeorm";

@Entity('match')
export class Match {
	@PrimaryGeneratedColumn()
	match_id: number;

	@Column('int', {default: 0})
	score_1: number;

	@Column('int', {default: 0})
	score_2: number;

	@ManyToOne(() => User)
	players: User[];

	@Column('varchar')
	mode:	string;
}
