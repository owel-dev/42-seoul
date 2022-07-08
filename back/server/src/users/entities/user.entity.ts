import { Stat } from "src/stats/entities/stat.entity";
import { Column, Entity, JoinColumn, ManyToOne, OneToOne, PrimaryColumn } from "typeorm";

@Entity('users')
export class User {
	@PrimaryColumn()
	intra_id: string;

	@Column()
	nickname: string;

	@Column()
	intra_email: string;

	@Column()
	avatar: string;

	@Column()
	status: string;

	@Column()
	role: string;

	@Column()
	channel_id: string;

	@OneToOne(() => Stat, (stat) => stat.user, {
		cascade: true,
	})
	stats: Stat;
}
